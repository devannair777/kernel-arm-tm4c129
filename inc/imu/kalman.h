#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "filter.h"

typedef struct
{
    Filter super;
    uint16_t width;
    uint16_t height;
}Kalman;

void Kalman_ctor(Kalman * const me, int16_t x0,int16_t y0,
                    uint16_t w0, uint16_t h0);
void Kalman_draw(Kalman const* const me);
uint16_t Kalman_area(Kalman const * const me);


#endif // __KALMAN_H__