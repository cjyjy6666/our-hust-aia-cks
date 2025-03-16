#ifndef __CAR_H__
#define __CAR_H__
#include"allfunc.h"
struct car_light;
struct car_ac;
typedef struct
{
   clock_t light_time;
   clock_t wiper_time;
   clock_t ac_time; 
}Car_Timer;
typedef struct car_light
{
    int right;
    int left;
    int fog;
    int near_light;
    int far_light;
    int left_blink_state;
    int right_blink_state;
}car_light;
typedef struct car_ac 
{
    int ac_state;//0:off 1:auto 2:cold 3:heat 4:
    int fresh_air;
    int circulate;
    int defog;
    int target_temp;
    int current_temp;
    int cur_t;//backup current_temp
}car_ac;
typedef struct CarStatus
{
    car_light light_s;
    car_ac ac_s;
    Car_Timer timer;
}CarStatus;


void init_car_status(CarStatus *state);
//CarStatus* get_car_status(void);
int check_timer_expire(clock_t* timer, clock_t interval);

#endif