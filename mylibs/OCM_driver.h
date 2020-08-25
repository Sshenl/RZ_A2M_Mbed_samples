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

/*字节*/		
void A_SendChar(uint8 c);

/*指令帧头*/	
void A_SendBeginCMD(void);

/*指令帧尾*/	
void A_SendEndCMD(void);

/*握手*/		
void A_HandUp(void);

/*清屏*/		
void A_CleanScreen(void);

/*颜色设置*/	
void A_SetColor(uint16 FColour,uint16 BColour);

/*单点颜色设置*/  
void A_SetPtColor(uint8 FColorL, uint8 FColorR);

/*字符显示模式*/
void A_SetCharMode(uint8 Char_mode,uint16 Colour);

/*背光调节*/
void A_SetBackLight(uint8 light_level);

/*sweep direcition*/ 
void ScanMode(uint8 LR);

/*蜂鸣器*/		
void A_Buzzer(uint8 BuzzerTpye,uint8 DelayTime);		  //Time(1字节): 鸣叫时间长度为10ms*Time

/*字符串*/		
void A_PutString(uint16 x,uint16 y,uint8 Font,char *string); 

/*画点*/		
void A_DrawDot(uint16 x0,uint16 y0);

/*画线*/		
void A_DrawLine(uint16 x0,uint16 y0,uint16 x1,uint16 y1);

/*圆形 */
void A_DrawCirCle(uint8_t mode, uint16 x0,uint16 y0, uint8_t r0);

/*长方形*/ 
void A_DrawRec(uint16 x0,uint16 y0,uint16 x1,uint16 y1, uint8 mode);

/*显示图片*/	
void A_DisImage(uint16 Picture_ID);

/*保存屏幕图片*/	
void A_SaveScreen(uint16 Picture_ID);

/*触摸设置*/	
void A_SetTP(void);

/*触摸体验*/	
void A_TestTP(void);

/*触摸控制*/    
void A_CtrlTP(uint8 TPMode);

/*显示时间*/	
void A_DisTime(uint8 DisTimeEN);

/*图片剪切*/	
void DisCut_Image(uint16 X,uint16 Y,uint8 ID,uint16 X1,uint16 Y1,uint16 Pic_W,uint16 Pic_H,uint16 MaskEn);

/*图形光标*/	
void TP_DisCursor(uint8 DisMode,uint16 x,uint16 y,uint8 ID) ;

/*文本跟随光标*/	
void TP_DisTextCursor(uint8 DisMode,uint8 Width,uint8 Height);

/*图层显示操作*/	
void DisplyLayer(uint8 DisMode,uint16 Parameter);

/*写图层功能*/	
void WriteLayer(uint8 layer) ;  

/*设置字符的底色显示*/ 	
void SetCharBackColor(uint8 mode,uint16 color);

//关闭背光 
void CloseBackLight(void);
 
//开背光
void OpenBackLight(void);

//设置背景色
void SetBackcolor(uint8 high, uint8 low);

//屏幕初始化
void OCMInit(void);

//获取触摸坐标
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
//发送指令字符
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
//握手指令
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
//清屏指令
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
//颜色指令
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
//单点颜色指令
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
//字符显示
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
//背光调节
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
//蜂鸣器调节
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
//字符串显示
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
//画点
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
//画线
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
//圆形显示
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
//矩形显示
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
//全屏图片显示
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
//保存屏幕图片
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
//触摸校准
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
//触摸体验
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
//触摸控制
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
//绿底红字时间显示		 
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
* 名    称：  DisCut_Image()
* 功    能： 图片剪切
* 入口参数：X,Y    区域显示坐标
            X1Y1   图片内部地址
            ID	   图片编号	
			Pic_W  剪切图像宽
            Pic_H  剪切图像高
			MaskEn：保留，一字节	                  　　　　　           
* 出口参数： 无
**************************************/
void DisCut_Image(uint16 X,uint16 Y,uint8 ID,uint16 X1,uint16 Y1,uint16 Pic_W,uint16 Pic_H,uint16 MaskEn)
{
   A_SendBeginCMD();
   A_SendChar(0x37);		   
   A_SendChar(0);
   A_SendChar(14);  //长度
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
* 名    称： TP_DisCursor()
* 功    能： 图形光标
* 入口参数：DisMode：显示的方式
			x,y：光标的显示位置
			ID：图形光标的编号		                         
         
出口参数： 无		 
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
* 名    称： TP_DisTextCursor()
* 功    能： 文本跟随光标
* 入口参数：DisMode：显示的方式
			Width：光标的显示位置
			Height：图形光标的编号		                         
         
出口参数： 无		 
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
* 名    称： DisplyLayer(uint8 DisMode，uint16 Parameter)
* 功    能： 图层显示操作
* 入口参数：DisMode 图层显示的模式
			Parameter    图层显示方式1字节/过滤色的范围2字节                   
         
出口参数： 无		 
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
* 名    称： WriteLayer()
* 功    能：  写图层功能
* 入口参数：layer  图层   01：写图层1 （默认）	  02：写图层2                        
         
出口参数： 无		 
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
* 名    称： SetCharBackColor()
* 功    能： 设置字符的底色显示
* 入口参数： mode:0   无底色，叠加在当前画面上	mode:1   有底色，底色由用户设置   color: 字符的底色
* 出口参数： 无
****************************************************************************/
void SetCharBackColor(uint8 mode,uint16 color)
{
	A_SendBeginCMD();
	A_SendChar(0x08); //指令码
	A_SendChar(0);	  //数据长度
	A_SendChar(3);	  //数据长度
	A_SendChar(mode);
	A_SendChar((color>>8)&0xff);
	A_SendChar(color&0xff);
	A_SendEndCMD();
}

//关背光
void CloseBackLight(void)
{
	A_SendBeginCMD();
	A_SendChar(0x09);		   
	A_SendChar(0x00);
	A_SendChar(0x00);		
	A_SendEndCMD(); 	
}

//开背光
void OpenBackLight(void)
{
	A_SendBeginCMD();
	A_SendChar(0x0a);		   
	A_SendChar(0x00);
    A_SendChar(0x00);		
    A_SendEndCMD();
}

//设置背景色
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

//初始化
void OCMInit(void)
{
	OpenBackLight();            //开启背光
	SetBackcolor(0xff, 0xff);   //将背景色设置为白色
	A_CleanScreen();            //以背景色刷屏
	A_SetBackLight(0x7f);       // 背光亮度
	//字体颜色设置为黑色
	A_SendBeginCMD();
	A_SendChar(0x06);
	A_SendChar(0x00);
	A_SendChar(0x02);
	A_SendChar(0x00);
	A_SendChar(0x00);
	A_SendEndCMD();
}

/******************************* 
* 获取触摸坐标
* 输入：x，y坐标buffer的地址
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

