#ifndef __FILTER_H__
#define __FILTER_H__

#include<stdint.h>

typedef struct Filter {

    int16_t x;
    int16_t y;

}Filter;

void Filter_ctor(Filter * const me,int16_t x0,int16_t y0);
void Filter_moveBy(Filter * const me,int16_t dx,int16_t dy);
uint16_t Filter_distanceFrom(Filter const * const me,const Filter * filter);

#endif // __FILTER_H__