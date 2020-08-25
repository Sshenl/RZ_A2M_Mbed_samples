#ifndef _LCD_DISP_
#define _LCD_DISP_

#include "mbed.h"
#include "OCM_driver.h"

#define NORMAL_DISP 0
#define ALARM_DISP  1
#define RETURN_DISP 2

#define ALARM_PAUSE 0
#define ALARM_PLAY  1

static int sys_status = 0; // 0:normal; 1:alarm

static int LCD_mode = NORMAL_DISP;
static int play_mode = ALARM_PAUSE;
static uint16_t TP_buffer[2] = {0};

void Touch_check(void);
void Page_refresh(int mode);
void Light_DISP(void);

/*----------------------------------------------------------------*/
void Touch_check(void)
{
    if (A_GetTP(TP_buffer))
    {
        //PLAY or PAUSE
        if (LCD_mode == ALARM_DISP && 
            215 <= TP_buffer[0] && TP_buffer[0] <= 295 && 200 <= TP_buffer[1] && TP_buffer[1] <= 260)
        {
            if (play_mode == ALARM_PAUSE) play_mode = ALARM_PLAY;
            else play_mode = ALARM_PAUSE;
            Page_refresh(ALARM_DISP);
        }
        //RETURN
        else if (LCD_mode == ALARM_DISP && 
                 95 <= TP_buffer[0] && TP_buffer[0] <= 175 && 280 <= TP_buffer[1] && TP_buffer[1] <= 340)
        {
            if (sys_status == 1)
                Page_refresh(RETURN_DISP);
            else {
                play_mode = ALARM_PAUSE;
                Page_refresh(NORMAL_DISP);
            }
        }
        //YES
        else if (LCD_mode == RETURN_DISP && 
                 235 <= TP_buffer[0] && TP_buffer[0] <= 305 && 260<= TP_buffer[1] && TP_buffer[1] <= 320) 
        {
            play_mode = ALARM_PAUSE;
            Page_refresh(NORMAL_DISP);
        }
        //NO
        else if (LCD_mode == RETURN_DISP && 
                 455 <= TP_buffer[0] && TP_buffer[0] <= 525 && 260<= TP_buffer[1] && TP_buffer[1] <= 320) 
        {
            Page_refresh(ALARM_DISP);
        }
    }
}


void Page_refresh(int mode)
{
    LCD_mode = mode;
    A_CleanScreen();
    Light_DISP();
    if (LCD_mode == NORMAL_DISP){
        A_SetPtColor(0x00, 0x00);
        A_PutString(100,100,0x13,"当前状态正常");
        //A_PutString(20,450,0x12,"*NOTE: It indicates that you are under attack when the red LED is on; otherwise, you are safe.");
    }
    else if (LCD_mode == ALARM_DISP) {
        A_SetPtColor(0xF8, 0x00);
        A_PutString(100,100,0x13,"注意！您可能正受到攻击");
        A_SetPtColor(0xDE, 0xFB);
        A_DrawRec(100,290,170,330,0x01); //RETURN
        A_SetPtColor(0x00, 0x00);
        A_PutString(100,220,0x14,"放音控制: ");
        A_PutString(110,300,0x14,"返回");
        //A_PutString(20,450,0x12,"*NOTE: It indicates that you are under attack when the red LED is on; otherwise, you are safe.");
        if (play_mode == ALARM_PAUSE){
            A_SetPtColor(0xDE, 0xFB);
            A_DrawRec(220,210,290,250,0x01); //PAUSE
            A_SetPtColor(0x00, 0x00);
            A_PutString(230,220,0x14,"暂停");
        }
        else{
            A_SetPtColor(0xDE, 0xFB);
            A_DrawRec(220,210,290,250,0x01); //PLAY
            A_SetPtColor(0x04, 0xA0);
            A_PutString(230,220,0x14,"播放");
        }
    }
    else if (LCD_mode == RETURN_DISP) {
        A_SetPtColor(0xDE, 0xFB);
        A_DrawRec(240,270,300,310,0x01); //YES
        A_DrawRec(460,270,520,310,0x01); //NO
        A_SetPtColor(0x00, 0x00);
        A_PutString(140,120,0x13,"您可能仍在受到攻击，确定要返回吗?");
        A_PutString(260,280,0x14,"是");
        A_PutString(480,280,0x14,"否");
    }
    else 
    {
        A_CleanScreen();
    }
}

void Light_DISP(void)
{
    uint16_t G_x = 650;
    uint16_t G_y = 100;
    uint16_t R_x = 700;
    uint16_t R_y = 100;
    uint8_t  r0 = 12;

    if (LCD_mode == ALARM_DISP || LCD_mode == NORMAL_DISP){
        //normal
        if (sys_status == 0){
            A_SetPtColor(0x06, 0xe0);
            A_DrawCirCle(0x01, G_x, G_y, r0);
            A_SetPtColor(0xFE, 0x59);
            A_DrawCirCle(0x01, R_x, R_y, r0);
            A_SetPtColor(0x00, 0x00);
            A_DrawCirCle(0x00, G_x, G_y, r0);
            A_DrawCirCle(0x00, R_x, R_y, r0);
        }
        //alarm
        else if (sys_status == 1) {
            A_SetPtColor(0xCF, 0xF9);
            A_DrawCirCle(0x01, G_x, G_y, r0);
            A_SetPtColor(0xF8, 0x00);
            A_DrawCirCle(0x01, R_x, R_y, r0);
            A_SetPtColor(0x00, 0x00);
            A_DrawCirCle(0x00, G_x, G_y, r0);
            A_DrawCirCle(0x00, R_x, R_y, r0);
        }
    }
    else{
        A_SetPtColor(0xFF, 0xFF);
        A_DrawCirCle(0x01, G_x, G_y, r0);
        A_DrawCirCle(0x01, R_x, R_y, r0);
    }
}

#endif
