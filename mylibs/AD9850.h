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
//              ad9850��λ(����ģʽ)                 //
//---------------------------------------------------//
void ad9850_reset()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest�ź�
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
}
//***************************************************//
//              ad9850��λ(����ģʽ)                 //
//---------------------------------------------------//
void ad9850_reset_serial()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest�ź�
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
	//w_clk�ź�
	p2_8_L;//ad9850_w_clk=0;
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//fq_up�ź�
	p2_9_L;//ad9850_fq_up=0;
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
void ad9850_reset_serial_double()
{
	p2_8_L;//ad9850_w_clk=0;
	p2_10_L;//ad9850_w_clk=0;
	p2_9_L;//ad9850_fq_up=0;
	//rest�ź�
	p2_7_L;//ad9850_rest=0;
	p2_7_H;//ad9850_rest=1;
	p2_7_L;//ad9850_rest=0;
	//w_clkL�ź�
	p2_8_L;//ad9850_w_clk=0;
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//w_clkR�ź�
	p2_10_L;//ad9850_w_clk=0;
	p2_10_H;//ad9850_w_clk=1;
	p2_10_L;//ad9850_w_clk=0;
	//fq_up�ź�
	p2_9_L;//ad9850_fq_up=0;
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
//***************************************************//
//          ��ad9850��д����������(����)             //
//---------------------------------------------------//
void ad9850_wr_parrel(unsigned char w0,double frequence)
{
	unsigned char w;
	long int y;
	double x;
	//����Ƶ�ʵ�HEXֵ
	x=4294967295/125;//�ʺ�125M����
	//���ʱ��Ƶ�ʲ�Ϊ125MHZ���޸ĸô���Ƶ��ֵ����λMHz ������
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;
	//дw0����
	w=w0;   
	//P1=w;      //w0
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//дw1����
	w=(y>>24);
	//P1=w;      //w1
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//дw2����
	w=(y>>16);
	//P1=w;      //w2
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//дw3����
	w=(y>>8);
	//P1=w;      //w3
	p2_8_H;//ad9850_w_clk=1;
	p2_8_L;//ad9850_w_clk=0;
	//дw4����
	w=(y>>=0);
	//P1=w;      //w4
	p2_8_H;//ad9850_w_clk=1; 
	p2_8_L;//ad9850_w_clk=0;
	//����ʼ��
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
//***************************************************//
//          ��ad9850��д����������(����)             //
//---------------------------------------------------//
void ad9850_wr_serial(unsigned char w0,double frequence)
{
	unsigned char i,w;
	long int y;
	double x;
	//����Ƶ�ʵ�HEXֵ
	x=4294967295/125;//�ʺ�125M����
	//���ʱ��Ƶ�ʲ�Ϊ180MHZ���޸ĸô���Ƶ��ֵ����λMHz  ������
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;
	//дw4����
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw3����
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw2����
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw1����
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw0����
	w=w0;   
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//����ʼ��
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}
void ad9850_wr_serial_double(unsigned char w0, unsigned char w1, double frequence, double frequence2)
{
	unsigned char i,w;
	long int y;
    long int y2;
	double x;
	//����Ƶ�ʵ�HEXֵ
	x=4294967295/125;//�ʺ�125M����
	//���ʱ��Ƶ�ʲ�Ϊ180MHZ���޸ĸô���Ƶ��ֵ����λMHz  ������
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;

    frequence2=frequence2/1000000;
	frequence2=frequence2*x;
    y2=frequence2;
	
	//���
	//дw4����
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw3����
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw2����
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw1����
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	//дw0����
	w=w0;   
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_8_H;//ad9850_w_clk=1;
		p2_8_L;//ad9850_w_clk=0;
	}
	
	//�Ҳ�
    //y = y2;
	//дw4����
	w=(y2>>=0);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//дw3����
	w=(y2>>8);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//дw2����
	w=(y2>>16);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//дw1����
	w=(y2>>24);
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	//дw0����
	w=w1;
	for(i=0;i<8;i++)
	{
		if ((w>>i)&0x01) p1_1_H;
		else p1_1_L;//ad9850_bit_data=(w>>i)&0x01;
		p2_10_H;//ad9850_w_clk=1;
		p2_10_L;//ad9850_w_clk=0;
	}
	
	//����ʼ��
	p2_9_H;//ad9850_fq_up=1;
	p2_9_L;//ad9850_fq_up=0;
}

#endif
