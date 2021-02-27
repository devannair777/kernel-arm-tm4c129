#include "imu/filter.h"

void Filter_ctor(Filter * const me,int16_t x0,int16_t y0)
{
    me->x = x0;
    me->y = y0;
}
void Filter_moveBy(Filter * const me,int16_t dx,int16_t dy)
{
    me->x += dx;
    me->y += dy;
}
uint16_t Filter_distanceFrom(Filter const * const me,const Filter * filter)
{
    int16_t dx = me->x - filter->x;
    int16_t dy = me->y - filter->y;

    return dx + dy;
}