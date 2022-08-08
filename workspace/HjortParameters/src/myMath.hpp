#ifndef MY_MATH_H
#define MY_MATH_H
//#include <Math.h>
#include <stdint.h>

void cmsis_arm_variance(float *pSrc, uint32_t blockSize, float *pResult);
float variance(float *x, int len);
float *derivative(float *x, int len);
float mean(float *x, int len);
float stdd(float *x, int len);


#endif