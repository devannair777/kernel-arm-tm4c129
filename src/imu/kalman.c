#include "imu/kalman.h"

void Kalman_ctor(Kalman * const me, int16_t x0,int16_t y0,
                    uint16_t w0, uint16_t h0)
{
    Filter_ctor(&me->super,x0,y0);
    me->width = w0;
    me->height = h0;
}
void Kalman_draw(Kalman const * const me)
{
    //Draw something
}
uint16_t Kalman_area(Kalman const * const me)
{
    return (uint32_t) me->width * (uint32_t) me->height;
}