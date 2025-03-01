#include"allfunc.h"

#ifndef __CAR_H__
#define __CAR_H__
typedef struct
{
   clock_t light_time;
   clock_t wiper_time;
   clock_t ac_time; 
}Car_Timer;
typedef struct
{
    struct car_light light_status;
    Car_Timer timer;
}CarStatus;

//void init_car_status();
CarStatus* get_car_status(void);
int check_timer_expire(clock_t *timer, clock_t interval);

#endif