#ifndef _OCM_Drive_
#define _OCM_Drive_

#include "mbed.h"

#define uint8  				unsigned char
#define uint16				unsigned short int

#define A_HandUp_ID			0x00
#define A_CleanScreen_ID	0x02
#define A_SetColor_ID		0x05
#define A_SetPt_Color       0x06
#define A_SetCharMode_ID	0x08
#define A_Char_mode_00		0x00
#define A_Char_mode_0C		0x01
#define A_Char_mode_90		0x80
#define A_Char_mode_9C		0x81
#define A_SetBackLight_ID	0x0b
#define A_Buzzer_ID			0x0d
#define	A_Buzzer1			0x00
#define	A_Buzzer2			0x01
#define	A_Buzzer3			0x02
#define	A_Buzzer4			0x03
#define A_Font_Size16		0x12
#define A_Font_Size24		0x14
#define A_Font_Size32		0x13
#define A_DrawDot_ID		0x21
#define A_DrawLine_ID		0x23
#define A_DisImage_ID		0x30
#define A_SetTP_ID			0x50
#define A_TestTP_ID			0x54
#define A_CtrlTP_ID			0x52
#define A_TP_PressD			0x01
#define A_TP_Press100ms		0x03
#define A_DisTime_ID		0x60
#define A_ScanMode_ID		0x0C
#define A_DrawRec_ID		0x27
#define A_SaveCurrentScreen 0x32

/*UART */
Serial A_uart(P7_3, P7_1, NULL, 9600);

void Delay_Nms(uint8 n);
void Delay(void);

/*�ֽ�*/		
void A_SendChar(uint8 c);

/*ָ��֡ͷ*/	
void A_SendBeginCMD(void);

/*ָ��֡β*/	
void A_SendEndCMD(void);

/*����*/		
void A_HandUp(void);

/*����*/		
void A_CleanScreen(void);

/*��ɫ����*/	
void A_SetColor(uint16 FColour,uint16 BColour);

/*������ɫ����*/  
void A_SetPtColor(uint8 FColorL, uint8 FColorR);

/*�ַ���ʾģʽ*/
void A_SetCharMode(uint8 Char_mode,uint16 Colour);

/*�������*/
void A_SetBackLight(uint8 light_level);

/*sweep direcition*/ 
void ScanMode(uint8 LR);

/*������*/		
void A_Buzzer(uint8 BuzzerTpye,uint8 DelayTime);		  //Time(1�ֽ�): ����ʱ�䳤��Ϊ10ms*Time

/*�ַ���*/		
void A_PutString(uint16 x,uint16 y,uint8 Font,char *string); 

/*����*/		
void A_DrawDot(uint16 x0,uint16 y0);

/*����*/		
void A_DrawLine(uint16 x0,uint16 y0,uint16 x1,uint16 y1);

/*Բ�� */
void A_DrawCirCle(uint8_t mode, uint16 x0,uint16 y0, uint8_t r0);

/*������*/ 
void A_DrawRec(uint16 x0,uint16 y0,uint16 x1,uint16 y1, uint8 mode);

/*��ʾͼƬ*/	
void A_DisImage(uint16 Picture_ID);

/*������ĻͼƬ*/	
void A_SaveScreen(uint16 Picture_ID);

/*��������*/	
void A_SetTP(void);

/*��������*/	
void A_TestTP(void);

/*��������*/    
void A_CtrlTP(uint8 TPMode);

/*��ʾʱ��*/	
void A_DisTime(uint8 DisTimeEN);

/*ͼƬ����*/	
void DisCut_Image(uint16 X,uint16 Y,uint8 ID,uint16 X1,uint16 Y1,uint16 Pic_W,uint16 Pic_H,uint16 MaskEn);

/*ͼ�ι��*/	
void TP_DisCursor(uint8 DisMode,uint16 x,uint16 y,uint8 ID) ;

/*�ı�������*/	
void TP_DisTextCursor(uint8 DisMode,uint8 Width,uint8 Height);

/*ͼ����ʾ����*/	
void DisplyLayer(uint8 DisMode,uint16 Parameter);

/*дͼ�㹦��*/	
void WriteLayer(uint8 layer) ;  

/*�����ַ��ĵ�ɫ��ʾ*/ 	
void SetCharBackColor(uint8 mode,uint16 color);

//�رձ��� 
void CloseBackLight(void);
 
//������
void OpenBackLight(void);

//���ñ���ɫ
void SetBackcolor(uint8 high, uint8 low);

//��Ļ��ʼ��
void OCMInit(void);

//��ȡ��������
bool A_GetTP(uint16_t pos_xy[2]);

/*------------------------------------------------------------------------------------- */
void Delay_Nms(uint8 n)
{
	uint8 i,j;
	for(i=0;i<n;i++)
		for(j=0;j<125;j++)
			;
}
void Delay(void)
{
  	Delay_Nms(200);
  	Delay_Nms(200);
  	Delay_Nms(200);
  	Delay_Nms(200);
  	Delay_Nms(200);
  	Delay_Nms(200);
  	Delay_Nms(200);
//  	Delay_Nms(200);
//  	Delay_Nms(200);
//  	Delay_Nms(200);
//  	Delay_Nms(200);
//  	Delay_Nms(200);
}
/**********************************************************************************************/
//����ָ���ַ�
/**********************************************************************************************/
void A_SendChar(unsigned char ch)
{
    A_uart.putc(ch);
}
void A_SendBeginCMD()
{
	A_SendChar(0xfd);
}
void A_SendEndCMD()
{
	A_SendChar(0xdd);
	A_SendChar(0xcc);
	A_SendChar(0xbb);
	A_SendChar(0xaa);	
}
/**********************************************************************************************/
//����ָ��
/**********************************************************************************************/
void A_HandUp(void)
{
	A_SendBeginCMD();
	A_SendChar(A_HandUp_ID);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendEndCMD();	
}
/**********************************************************************************************/
//����ָ��
/**********************************************************************************************/
void A_CleanScreen(void)
{
	A_SendBeginCMD();
	A_SendChar(A_CleanScreen_ID);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendEndCMD();
}
/**********************************************************************************************/
//��ɫָ��
/**********************************************************************************************/
void A_SetColor(uint16 FColour,uint16 BColour)
{ 
  	A_SendBeginCMD();
	A_SendChar(A_SetColor_ID);
	A_SendChar(0x00);
	A_SendChar(0x04);
  	A_SendChar((FColour>>8)&0xff);
  	A_SendChar(FColour&0xff);
	A_SendChar((BColour>>8)&0xff);
  	A_SendChar(BColour&0xff);
  	A_SendEndCMD();
}
/**********************************************************************************************/
//������ɫָ��
/**********************************************************************************************/
 void A_SetPtColor(uint8 FColorL, uint8 FColorR)
 {
	A_SendBeginCMD();
 	A_SendChar(0x06);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar(FColorL);
	A_SendChar(FColorR);
	A_SendEndCMD();
 }
/************************************************************************/
//scanMode
/************************************************************************/
 void ScanMode(uint8 LR)
{
	A_SendBeginCMD();
  	A_SendChar(A_ScanMode_ID);
	A_SendChar(0x00);
	A_SendChar(0x01);
	A_SendChar(LR);
  	A_SendEndCMD();		
}
/**********************************************************************************************/
//�ַ���ʾ
/**********************************************************************************************/
void A_SetCharMode(uint8 Char_mode,uint16 Colour)
{
  	A_SendBeginCMD();
  	A_SendChar(A_SetCharMode_ID);
	A_SendChar(0x00);
	A_SendChar(0x03);
	A_SendChar(Char_mode);
	A_SendChar((Colour>>8)&0xff);
  	A_SendChar(Colour&0xff);
  	A_SendEndCMD();		
}
/**********************************************************************************************/
//�������
/**********************************************************************************************/
void A_SetBackLight(uint8 light_level)
{
  	A_SendBeginCMD();
  	A_SendChar(A_SetBackLight_ID);
	A_SendChar(0x00);
	A_SendChar(0x01);
	A_SendChar(light_level);
  	A_SendEndCMD();		
}
/**********************************************************************************************/
//����������
/**********************************************************************************************/
void A_Buzzer(uint8 BuzzerTpye,uint8 DelayTime)
{
  	A_SendBeginCMD();
  	A_SendChar(A_Buzzer_ID);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar(BuzzerTpye);
	A_SendChar(DelayTime);
  	A_SendEndCMD();		
}
/**********************************************************************************************/
//�ַ�����ʾ
/**********************************************************************************************/
void A_PutString(uint16 x,uint16 y,uint8 Font,char *string) 
{
	uint16 len;
	len=strlen(string); 
	len=len+5;

	A_SendBeginCMD();
    A_SendChar(Font);
	A_SendChar((len>>8)&0xff);
    A_SendChar(len&0xff);
	A_SendChar((x>>8)&0xff);
    A_SendChar(x&0xff);
	A_SendChar((y>>8)&0xff);
	A_SendChar(y&0xff);
	do
	{
		A_SendChar(*string);
	}
	while(*string++);
	A_SendEndCMD();
}


/**********************************************************************************************/
//����
/**********************************************************************************************/
void A_DrawDot(uint16 x0,uint16 y0)
{
    A_SendBeginCMD();
    A_SendChar(A_DrawDot_ID);
	A_SendChar(0x00);
	A_SendChar(0x04);
	A_SendChar((x0>>8)&0xff);
    A_SendChar(x0&0xff);
	A_SendChar((y0>>8)&0xff);
	A_SendChar(y0&0xff);
    A_SendEndCMD();	
}
/**********************************************************************************************/
//����
/**********************************************************************************************/
void A_DrawLine(uint16 x0,uint16 y0,uint16 x1,uint16 y1)
{
  	A_SendBeginCMD();
  	A_SendChar(A_DrawLine_ID);
	A_SendChar(0x00);
	A_SendChar(0x08);
	A_SendChar((x0>>8)&0xff);
    A_SendChar(x0&0xff);
	A_SendChar((y0>>8)&0xff);
	A_SendChar(y0&0xff);
	A_SendChar((x1>>8)&0xff);
    A_SendChar(x1&0xff);
	A_SendChar((y1>>8)&0xff);
	A_SendChar(y1&0xff);
  	A_SendEndCMD();	
}
/**********************************************************************************************/
//Բ����ʾ
/**********************************************************************************************/
void A_DrawCirCle(uint8_t mode, uint16 x0,uint16 y0, uint8_t r0)
{
    A_SendBeginCMD();
    A_SendChar(0x26);
    A_SendChar(0x00);
	A_SendChar(0x06);
    A_SendChar(mode);
    A_SendChar((x0>>8)&0xff);
    A_SendChar(x0&0xff);
	A_SendChar((y0>>8)&0xff);
	A_SendChar(y0&0xff);
    A_SendChar(r0);
    A_SendEndCMD();	
}

/**********************************************************************************************/
//������ʾ
/**********************************************************************************************/
 void A_DrawRec(uint16 x0,uint16 y0,uint16 x1,uint16 y1, uint8 mode)
{
  	A_SendBeginCMD();
  	A_SendChar(0x27);
	A_SendChar(0x00);
	A_SendChar(0x09);
	A_SendChar(mode);
	A_SendChar((x0>>8)&0xff);
    A_SendChar(x0&0xff);
	A_SendChar((y0>>8)&0xff);
	A_SendChar(y0&0xff);
	A_SendChar((x1>>8)&0xff);
    A_SendChar(x1&0xff);
	A_SendChar((y1>>8)&0xff);
	A_SendChar(y1&0xff);
  	A_SendEndCMD();	
}
/**********************************************************************************************/
//ȫ��ͼƬ��ʾ
/**********************************************************************************************/
void A_DisImage(uint16 Picture_ID)
{
  	A_SendBeginCMD();
  	A_SendChar(A_DisImage_ID);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar((Picture_ID>>8)&0xff);
    A_SendChar(Picture_ID&0xff);
  	A_SendEndCMD();
}

/**********************************************************************************************/
//������ĻͼƬ
/**********************************************************************************************/
void A_SaveScreen(uint16 Picture_ID)
{
  	A_SendBeginCMD();
  	A_SendChar(A_SaveCurrentScreen);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar((Picture_ID>>8)&0xff);
    A_SendChar(Picture_ID&0xff);
  	A_SendEndCMD();
}


/**********************************************************************************************/
//����У׼
/**********************************************************************************************/
void A_SetTP(void)
{	
  	A_SendBeginCMD();
  	A_SendChar(A_SetTP_ID);
	A_SendChar(0x00);
	A_SendChar(0x04);
	A_SendChar(0x55);
    A_SendChar(0xaa);
	A_SendChar(0x5a);
	A_SendChar(0xa5);
  	A_SendEndCMD();
}
/**********************************************************************************************/
//��������
/**********************************************************************************************/
void A_TestTP(void)
{	
  	A_SendBeginCMD();
  	A_SendChar(0x53);
	A_SendChar(0x00);
	A_SendChar(0x04);
	A_SendChar(0x55);
    A_SendChar(0xaa);
	A_SendChar(0x5a);
	A_SendChar(0xa5);
  	A_SendEndCMD();
}
/**********************************************************************************************/
//��������
/**********************************************************************************************/
void A_CtrlTP(uint8 TPMode)
{
  	A_SendBeginCMD();
  	A_SendChar(A_CtrlTP_ID);
	A_SendChar(0x00);
	A_SendChar(0x01);
	A_SendChar(TPMode);
  	A_SendEndCMD();	
}
/**********************************************************************************************/
//�̵׺���ʱ����ʾ		 
/**********************************************************************************************/
void A_DisTime(uint8 DisTimeEN)
{
  	A_SendBeginCMD();
  	A_SendChar(A_DisTime_ID);
	A_SendChar(0x00);
	A_SendChar(0x0a);
    A_SendChar(DisTimeEN);
	A_SendChar(0x02);
	A_SendChar(0xfc);
	A_SendChar(0x00);
	A_SendChar(0x07);
	A_SendChar(0xe0);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendChar(0x00);
  	A_SendEndCMD();
}

/*********************************************
* ��    �ƣ�  DisCut_Image()
* ��    �ܣ� ͼƬ����
* ��ڲ�����X,Y    ������ʾ����
            X1Y1   ͼƬ�ڲ���ַ
            ID	   ͼƬ���	
			Pic_W  ����ͼ���
            Pic_H  ����ͼ���
			MaskEn��������һ�ֽ�	                  ����������           
* ���ڲ����� ��
**************************************/
void DisCut_Image(uint16 X,uint16 Y,uint8 ID,uint16 X1,uint16 Y1,uint16 Pic_W,uint16 Pic_H,uint16 MaskEn)
{
   A_SendBeginCMD();
   A_SendChar(0x37);		   
   A_SendChar(0);
   A_SendChar(14);  //����
   A_SendChar(X/256);
   A_SendChar(X%256);
   A_SendChar(Y/256);
   A_SendChar(Y%256);
   A_SendChar(ID);
   A_SendChar(X1/256);
   A_SendChar(X1%256);
   A_SendChar(Y1/256);
   A_SendChar(Y1%256);
   A_SendChar(Pic_W/256);
   A_SendChar(Pic_W%256);  
   A_SendChar(Pic_H/256);
   A_SendChar(Pic_H%256);
   A_SendChar(MaskEn%256);
   A_SendEndCMD();
} 

/****************************************************************************
* ��    �ƣ� TP_DisCursor()
* ��    �ܣ� ͼ�ι��
* ��ڲ�����DisMode����ʾ�ķ�ʽ
			x,y��������ʾλ��
			ID��ͼ�ι��ı��		                         
         
���ڲ����� ��		 
****************************************************************************/
void TP_DisCursor(uint8 DisMode,uint16 x,uint16 y,uint8 ID) 
{
	A_SendBeginCMD();
	A_SendChar(0x80);
	A_SendChar(0);
	A_SendChar(6);
    A_SendChar(DisMode);
	A_SendChar(x/256);
	A_SendChar(x%256);
	A_SendChar(y/256);
	A_SendChar(y%256);
	A_SendChar(ID);
	A_SendEndCMD();
}

/****************************************************************************
* ��    �ƣ� TP_DisTextCursor()
* ��    �ܣ� �ı�������
* ��ڲ�����DisMode����ʾ�ķ�ʽ
			Width��������ʾλ��
			Height��ͼ�ι��ı��		                         
         
���ڲ����� ��		 
****************************************************************************/
void TP_DisTextCursor(uint8 DisMode,uint8 Width,uint8 Height) 
{
	A_SendBeginCMD();
	A_SendChar(0x85);
	A_SendChar(0);
	A_SendChar(3);
    A_SendChar(DisMode);
	A_SendChar(Width);
	A_SendChar(Height);
	A_SendEndCMD();
}

/****************************************************************************
* ��    �ƣ� DisplyLayer(uint8 DisMode��uint16 Parameter)
* ��    �ܣ� ͼ����ʾ����
* ��ڲ�����DisMode ͼ����ʾ��ģʽ
			Parameter    ͼ����ʾ��ʽ1�ֽ�/����ɫ�ķ�Χ2�ֽ�                   
         
���ڲ����� ��		 
****************************************************************************/
void DisplyLayer(uint8 DisMode,uint16 Parameter) 
{
	A_SendBeginCMD();
	A_SendChar(0x91);
	A_SendChar(0);
	switch(DisMode)
	{
		case 1:		A_SendChar(2);	  	break;
		case 2:		A_SendChar(3);	  	break;
	}
    A_SendChar(DisMode);
 	switch(DisMode)
	{
		case 1:		A_SendChar(Parameter);  	break;  
		case 2:		A_SendChar(Parameter/256); A_SendChar(Parameter%256); 	break;
	}
	A_SendEndCMD();
}

/****************************************************************************
* ��    �ƣ� WriteLayer()
* ��    �ܣ�  дͼ�㹦��
* ��ڲ�����layer  ͼ��   01��дͼ��1 ��Ĭ�ϣ�	  02��дͼ��2                        
         
���ڲ����� ��		 
****************************************************************************/
void WriteLayer(uint8 layer) 
{
	A_SendBeginCMD();
	A_SendChar(0x90);
	A_SendChar(0);
	A_SendChar(1);
    A_SendChar(layer);
	A_SendEndCMD();
}

/****************************************************************************
* ��    �ƣ� SetCharBackColor()
* ��    �ܣ� �����ַ��ĵ�ɫ��ʾ
* ��ڲ����� mode:0   �޵�ɫ�������ڵ�ǰ������	mode:1   �е�ɫ����ɫ���û�����   color: �ַ��ĵ�ɫ
* ���ڲ����� ��
****************************************************************************/
void SetCharBackColor(uint8 mode,uint16 color)
{
	A_SendBeginCMD();
	A_SendChar(0x08); //ָ����
	A_SendChar(0);	  //���ݳ���
	A_SendChar(3);	  //���ݳ���
	A_SendChar(mode);
	A_SendChar((color>>8)&0xff);
	A_SendChar(color&0xff);
	A_SendEndCMD();
}

//�ر���
void CloseBackLight(void)
{
	A_SendBeginCMD();
	A_SendChar(0x09);		   
	A_SendChar(0x00);
	A_SendChar(0x00);		
	A_SendEndCMD(); 	
}

//������
void OpenBackLight(void)
{
	A_SendBeginCMD();
	A_SendChar(0x0a);		   
	A_SendChar(0x00);
    A_SendChar(0x00);		
    A_SendEndCMD();
}

//���ñ���ɫ
void SetBackcolor(uint8_t high, uint8_t low)
{
	A_SendBeginCMD();
    A_SendChar(0x07);
    A_SendChar(0x00);
    A_SendChar(0x02);
    A_SendChar(high);
    A_SendChar(low);
	A_SendEndCMD();
}

//��ʼ��
void OCMInit(void)
{
	OpenBackLight();            //��������
	SetBackcolor(0xff, 0xff);   //������ɫ����Ϊ��ɫ
	A_CleanScreen();            //�Ա���ɫˢ��
	A_SetBackLight(0x7f);       // ��������
	//������ɫ����Ϊ��ɫ
	A_SendBeginCMD();
	A_SendChar(0x06);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendEndCMD();
}

/******************************* 
* ��ȡ��������
* ���룺x��y����buffer�ĵ�ַ
*******************************/
bool A_GetTP(uint16_t pos_xy[2])
{
    uint16_t buffer[10] = {0};
    if (A_uart.readable())
    {
        uint16_t tmp = A_uart.getc();
        if (tmp == 0x0A)
            return 0;
        else 
        {
            buffer[0] = tmp;
            for (int i = 1; i < 10; i++)
                buffer[i] = A_uart.getc();
            pos_xy[0] = (buffer[2]<<8) + buffer[3];
            pos_xy[1] = (buffer[4]<<8) + buffer[5];
            return 1;
        }
    }
    else
        return 0;
}

#endif

