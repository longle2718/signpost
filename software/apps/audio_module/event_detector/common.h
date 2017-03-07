#ifndef __COMMON_H__
#define __COMMON_H__

#include "_kiss_fft_guts.h"

#define BUF_LEN     (512)
#define INC_LEN     (BUF_LEN/2)
#define FRE_LEN     (BUF_LEN/2)

#define S_SQ(a)     S_MUL((a),(a)) // scalar square
#define S_DIV(a,b)  S_MUL((a),SAMP_MAX/(b)) // a < b
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#define ABS(a)      (((a) < 0) ? -(a): (a))
// Magnitude Estimator 
// http://dspguru.com/book/export/html/62
#define ALPHA       ((kiss_fft_scalar)(0.947543636291*SAMP_MAX))
#define BETA        ((kiss_fft_scalar)(0.392485425092*SAMP_MAX))
#define MAG(r,i)    ( S_MUL(ALPHA,MAX(ABS((r)),ABS((i)))) + S_MUL(BETA,MIN(ABS((r)),ABS((i)))) )

#endif
