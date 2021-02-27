#ifndef __IMU_H__
#define __IMU_H__

#include <stdint.h>

void MPUCallbackFcn(void * pvCallbackdata,uint_fast8_t ui8Status);
void MPUFilter(float *pitchAngle, float *rollAngle,float *yawAngle);

typedef struct filter_param {
    float t_sample;
    float tau;
}f_param;

typedef float (*pfFilter) (f_param *f,float *s1_angle, float *s2_angle);

struct filter_structure{

    f_param f_coef;
    pfFilter filter_impl;
    float res_angle;

};


void* apply_filter (struct filter_structure * f);

#endif //__IMU_H__