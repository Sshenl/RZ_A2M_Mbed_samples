#ifndef AD9850
#define AD9850

#include "mbed.h"

/*GPIO */
DigitalOut data(P0_1);
DigitalOut fq_up(P0_3);
DigitalOut w_clk2(P0_5);
DigitalOut w_clk1(P0_4);
DigitalOut rest(P0_6);
DigitalOut test(P0_0);
#define p2_8_L w_clk1 = 0
#define p2_8_H w_clk1 = 1
#define p2_10_L w_clk2 = 0
#define p2_10_H w_clk2 = 1
#define p2_9_L fq_up = 0
#define p2_9_H fq_up = 1
#define p2_7_L rest = 0
#define p2_7_H rest = 1
#define p1_1_L data = 0
#define p1_1_H data = 1

/*DDS Function*/
//***************************************************//
//              ad9850复位(并口模式)                 //
//---------------------------------------------------//
void ad9850_reset()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest信号
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
}
//***************************************************//
//              ad9850复位(串口模式)                 //
//---------------------------------------------------//
void ad9850_reset_serial()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest信号
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
	//w_clk信号
	p2_8_L;//ad9850_w_clk=0;
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//fq_up信号
	p2_9_L;//ad9850_fq_up=0;
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
void ad9850_reset_serial_double()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_10_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest信号
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
	//w_clkL信号
	p2_8_L;//ad9850_w_clk=0;
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//w_clkR信号
	p2_10_L;//ad9850_w_clk=0;
	p2_10_H;//ad9850_w_clk=1;
	p2_10_L;//ad9850_w_clk=0;
	//fq_up信号
	p2_9_L;//ad9850_fq_up=0;
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
//***************************************************//
//          向ad9850中写命令与数据(并口)             //
//---------------------------------------------------//
void ad9850_wr_parrel(unsigned char w0,double frequence)
{
	unsigned char w;
	long int y;
	double x;
	//计算频率的HEX值
	x=4294967295/125;//适合125M晶振
	//如果时钟频率不为125MHZ，修改该处的频率值，单位MHz ！！！
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;
	//写w0数据
	w=w0;   
	//P1=w;      //w0
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//写w1数据
	w=(y>>24);
	//P1=w;      //w1
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//写w2数据
	w=(y>>16);
	//P1=w;      //w2
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//写w3数据
	w=(y>>8);
	//P1=w;      //w3
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//写w4数据
	w=(y>>=0);
	//P1=w;      //w4
	p2_8_H;//ad9850_w_clk=1; 
	p2_8_L;//ad9850_w_clk=0;
	//移入始能
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
//***************************************************//
//          向ad9850中写命令与数据(串口)             //
//---------------------------------------------------//
void ad9850_wr_serial(unsigned char w0,double frequence)
{
	unsigned char i,w;
	long int y;
	double x;
	//计算频率的HEX值
	x=4294967295/125;//适合125M晶振
	//如果时钟频率不为180MHZ，修改该处的频率值，单位MHz  ！！！
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;
	//写w4数据
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w3数据
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w2数据
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w1数据
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w0数据
	w=w0;   
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//移入始能
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
void ad9850_wr_serial_double(unsigned char w0, unsigned char w1, double frequence, double frequence2)
{
	unsigned char i,w;
	long int y;
    long int y2;
	double x;
	//计算频率的HEX值
	x=4294967295/125;//适合125M晶振
	//如果时钟频率不为180MHZ，修改该处的频率值，单位MHz  ！！！
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;

    frequence2=frequence2/1000000;
	frequence2=frequence2*x;
    y2=frequence2;
	
	//左侧
	//写w4数据
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w3数据
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w2数据
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w1数据
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//写w0数据
	w=w0;   
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	
	//右侧
    //y = y2;
	//写w4数据
	w=(y2>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//写w3数据
	w=(y2>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//写w2数据
	w=(y2>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//写w1数据
	w=(y2>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//写w0数据
	w=w1;
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	
	//移入始能
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}

#endif
