#include "sample_select.h"

#if (SAMPLE_PROGRAM_NO == 22)
// SAMPLE_PROGRAM_NO  22 : main proj

#if defined(TARGET_SEMB1402) || defined(TARGET_RZ_A2M_SBEV)
#error "Audio is not supported."
#endif

#include "mbed.h"
#include "AUDIO_GRBoard.h"
#include "mylibs/AD9850.h"
#include "mylibs/OCM_driver.h"
#include "mylibs/filter.h"
#include "mylibs/LCD_disp.h"

/*LED */
DigitalOut led1(LED1);
DigitalOut led2(LED2);

/*BUTTON */
//InterruptIn button(USER_BUTTON0);

/*UART */
Serial pc(USBTX, USBRX, NULL, 9600);


/*AUDIO */
#define WRITE_BUFF_NUM         (8)
#define READ_BUFF_NUM          (8)
#define MAIL_QUEUE_SIZE        (WRITE_BUFF_NUM + READ_BUFF_NUM + 1)
#define INFO_TYPE_WRITE_END    (0)
#define INFO_TYPE_READ_END     (1)
#define AUDIO_BUFF_SIZE        (40960)
//#define AUDIO_BUFF_SIZE        (4096)

AUDIO_GRBoard audio(0x80, WRITE_BUFF_NUM, READ_BUFF_NUM);

typedef struct {
    uint32_t info_type;
    void *   p_data;
    int32_t  result;
} mail_t;
Mail<mail_t, MAIL_QUEUE_SIZE> mail_box;

//32 bytes aligned! No cache memory
static uint8_t audio_read_buff[READ_BUFF_NUM][AUDIO_BUFF_SIZE] __attribute((section("NC_BSS"),aligned(32)));
double d_array[AUDIO_BUFF_SIZE/2];
double e_array[AUDIO_BUFF_SIZE/2];

static void callback_audio(void * p_data, int32_t result, void * p_app_data) {
    mail_t *mail = mail_box.alloc();

    if (mail == NULL) {
        pc.printf("error mail alloc\r\n");
    } else {
        mail->info_type = (uint32_t)p_app_data;
        mail->p_data    = p_data;
        mail->result    = result;
        mail_box.put(mail);
    }
}

int main() {
    rbsp_data_conf_t audio_write_conf = {&callback_audio, (void *)INFO_TYPE_WRITE_END};
    rbsp_data_conf_t audio_read_conf  = {&callback_audio, (void *)INFO_TYPE_READ_END};

    audio.power();
    audio.outputVolume(1, 1);
    audio.micVolume(1);

    // Read buffer setting
    for (int i = 0; i < READ_BUFF_NUM; i++) {
        if (audio.read(audio_read_buff[i], AUDIO_BUFF_SIZE, &audio_read_conf) < 0) {
            printf("read error\r\n");
        }
    }

    // DDS initialize
    ad9850_reset_serial_double();
    ad9850_wr_serial_double(0x00, 0x00, 20000, 38000);

    // LCD initialize
    OCMInit();
    Light_DISP();
    A_CtrlTP(0x01);

    double sum_input = 0;
    double sum_output = 0;
    double max_value[2] = {0};

    int warning_cnt = 0;
    int reset_cnt = 0;
    
    double Alarm_coefficient = 0;

    Page_refresh(NORMAL_DISP);

    while (1) {
        osEvent evt = mail_box.get();
        if (evt.status == osEventMail) {
            mail_t *mail = (mail_t *)evt.value.p;
            if ((mail->info_type == INFO_TYPE_READ_END) && (mail->result > 0)) 
            {
                int16_t* p = (int16_t*) mail->p_data;
                
                max_value[0] = 0.01;
                max_value[1] = 0.01;

                double zf[32];
                double zf2[29];

                /*High pass filtering */
                Highpass_441(d_array, zf, p, AUDIO_BUFF_SIZE/2, NULL, max_value);

                /*Alarm judgment */
                sum_input = 0;
                sum_output = 0;
                for (int i = 0; i < AUDIO_BUFF_SIZE/2; i++)
                {
                    sum_input += (p[i]*p[i]);
                    sum_output += (10000*10000*d_array[i]*d_array[i])/(max_value[1]*max_value[1]);
                }
                Alarm_coefficient = sum_output/sum_input;

                if (Alarm_coefficient < 50){
                    warning_cnt++;
                    if (warning_cnt >= 3){
                        reset_cnt = 0;
                        if (sys_status == 0){
                            sys_status = 1;
                            Page_refresh(ALARM_DISP);
                            //Light_DISP();
                        }
                    }
                }
                else{
                    reset_cnt++;
                    if (reset_cnt >= 3){
                        warning_cnt = 0;
                        if (sys_status == 1){
                            sys_status = 0;
                            Light_DISP();
                        }
                    }
                }
                //pc.printf("%.2f, ", Alarm_coefficient);
                
                /*Output signal processing */
                //conv(22, d_array, AUDIO_BUFF_SIZE/2);
                //Lowpass(e_array, zf2, d_array , AUDIO_BUFF_SIZE/2, NULL);
                for (int i = 0; i < AUDIO_BUFF_SIZE/2; i++){
                    if (!(LCD_mode == ALARM_DISP && play_mode == ALARM_PLAY))
                        p[i] = 0;
                    //else{
                        //p[i] = (int16_t) (3*abs(d_array[i]) );//*4*sin(2*3.1415926*22000*i/44100));
                    //}
                }
                
                audio.write(mail->p_data, mail->result, &audio_write_conf);
                led2 = !led2;
            }
            else
            {
                audio.read(mail->p_data, AUDIO_BUFF_SIZE, &audio_read_conf); // Resetting read buffer
            }

            mail_box.free(mail);
        }
        Touch_check();
    }
}

#endif
