#ifndef _FILTER_H_
#define _FILTER_H_

#include "mbed.h"
#include <cstdio>
#include <cstring>

void Highpass_441( double y[], double zf[],  int16_t *x, int lenX, const double zi[], double max_val[] )
{
	int i, j;

    double a[33]={1.000000,-7.783847,33.190380,-99.047948,228.615571,
	-429.977771,680.387506,-925.140366,1097.008493,-1146.513754,1064.396423,
	-882.827331,656.915874,-439.821250,265.457236,-144.574261,71.061324,
	-31.502664,12.578152,-4.513031,1.450567,-0.415928,0.105822,-0.023727,
	0.004648,-0.000786,0.000113,-0.000014,0.000001,-0.000000,0.000000,
	-0.000000,0.000000};

    double b[33]={0.000002,-0.000061,0.000950,-0.009498,0.068859,
	-0.385609,1.735242,-6.445185,20.141203,-53.709876,123.532715,
	-247.065429,432.364501,-665.176156,902.739069,-1083.286883,1150.992313,
	-1083.286883,902.739069,-665.176156,432.364501,-247.065429,123.532715,
	-53.709876,20.141203,-6.445185,1.735242,-0.385609,0.068859,-0.009498,
	0.000950,-0.000061,0.000002};

    int lenA = 33;
    int lenB = 33;

	int		na = lenA - 1, nb = lenB - 1;
	int		len = na>nb ? na : nb;

	bool	zi_null = zi==NULL;
    
	if( zf!=NULL ){
		memset( zf, 0, len*sizeof(double) );
		if( zi==NULL )
			zi = new double [len] ();
	}

	bool	zf_null = zf==NULL;
	if( zi!=NULL && zf==NULL )
		zf = new double [len] ();
    
	// 1.
	if( zf==NULL && zi==NULL ){
		y[0] = b[0] * x[0];
		for(i=1; i<lenX; i++ ){
			y[i] = 0;
			for(j=0; j<=nb; j++ ){
				if( i-j<0 )	break;
				y[i] += b[j] * x[i-j];
			}
			for(j=1; j<=na; j++ ){
				if( i-j<0 )	break;
				y[i] -= a[j] * x[i-j];
			}
		}

	}
	// 2.
	else{
		double		*A = new double [len+1] ();
		memcpy( A, a, lenA*sizeof(double) );
		double		*B = new double [len+1] ();
		memcpy( B, b, lenB*sizeof(double) );
		double		*zf_last = new double [len];
		memcpy( zf_last, zi, len*sizeof(double) );
        
		for( i=0; i<lenX; i++ ){
			y[i] = b[0] * (double)(x[i]) + zf_last[0];
            if (x[i] > max_val[0]) max_val[0] = x[i];
            if (y[i] > max_val[1]) max_val[1] = y[i];
			zf[len-1] = B[len] * (double)(x[i]) - A[len] * y[i];
			for( j=len-2; j>=0; j-- )
				zf[j] = B[j+1]*(double)(x[i]) + zf_last[j+1] - A[j+1]*y[i];
			memcpy( zf_last, zf, len*sizeof(double) );
		}

		delete	[]		A;
		delete	[]		B;
		delete	[]		zf_last;
		if(zi_null)	delete	[]		zi;
		if(zf_null)	delete	[]		zf;

	}
	return;
}

void conv (double freq, double *y, int leny)
{
    for (int i =0; i<leny; i++)
    {
        double shift_signal = 4*sin(2*3.14159*freq*1000*i/44100);
        y[i] = y[i] * shift_signal;
    }

    return;
}

void self_conv (double *y, int leny)
{
    for (int i =0; i<leny; i++)
    {
        y[i] = y[i] * y[i];
    }

    return;
}

void filter_test( double y[], int lenX )
{
    for (int k =0; k<lenX; k++)
    {
        y[k] = 0;
    }

    return;
}



void Lowpass( double y[], double zf[],  double *x, int lenX, const double zi[])
{
	int i, j;

    double a[]={1.000000,-22.230102,239.207503,-1659.027167,8331.142735,
    -32261.602289,100185.383304,-256161.814143,549445.941036,-1002199.632327,
    1570323.996162,-2129544.162629,2513191.475647,-2591019.021404,2339241.959828,
    -1851582.068634,1284863.007223,-780689.702566,414304.626778,-191285.229138,
    76409.807312,-26207.808826,7640.174112,-1867.291491,375.501104,-60.507355,
    7.512032,-0.674623,0.039008,-0.001091};

    double b[]={0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,
    0.000000,0.000000,0.000000,0.000000,0.000000};

    int lenA = 30;
    int lenB = 30;

	int		na = lenA - 1, nb = lenB - 1;
	int		len = na>nb ? na : nb;

	bool	zi_null = zi==NULL;
    
	if( zf!=NULL ){
		memset( zf, 0, len*sizeof(double) );
		if( zi==NULL )
			zi = new double [len] ();
	}

	bool	zf_null = zf==NULL;
	if( zi!=NULL && zf==NULL )
		zf = new double [len] ();
    
	// 1.
	if( zf==NULL && zi==NULL ){
		y[0] = b[0] * x[0];
		for(i=1; i<lenX; i++ ){
			y[i] = 0;
			for(j=0; j<=nb; j++ ){
				if( i-j<0 )	break;
				y[i] += b[j] * x[i-j];
			}
			for(j=1; j<=na; j++ ){
				if( i-j<0 )	break;
				y[i] -= a[j] * x[i-j];
			}
		}

	}
	// 2.
	else{
		double		*A = new double [len+1] ();
		memcpy( A, a, lenA*sizeof(double) );
		double		*B = new double [len+1] ();
		memcpy( B, b, lenB*sizeof(double) );
		double		*zf_last = new double [len];
		memcpy( zf_last, zi, len*sizeof(double) );
        
		for( i=0; i<lenX; i++ ){
			y[i] = b[0] * (double)(x[i]) + zf_last[0];
            //if (x[i] > max_val[0]) max_val[0] = x[i];
            //if (y[i] > max_val[1]) max_val[1] = y[i];
			zf[len-1] = B[len] * (double)(x[i]) - A[len] * y[i];
			for( j=len-2; j>=0; j-- )
				zf[j] = B[j+1]*(double)(x[i]) + zf_last[j+1] - A[j+1]*y[i];
			memcpy( zf_last, zf, len*sizeof(double) );
		}

		delete	[]		A;
		delete	[]		B;
		delete	[]		zf_last;
		if(zi_null)	delete	[]		zi;
		if(zf_null)	delete	[]		zf;

	}
	return;
}
#endif