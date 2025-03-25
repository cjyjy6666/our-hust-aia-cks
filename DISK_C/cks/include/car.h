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
    clock_t drive_time_s;
    clock_t drive_time_n;
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
typedef struct car_wiper
{
    int auto_w;
    int once;
    int fast;
    int slow;
    int rain;
    int cur_wip;
}car_wiper;
typedef struct car_drive
{
    int forward;
    int back;
    int park;
    int sport;
    int comfort;
    int view;
    double angle_s;
    double angle_n;
}car_drive;
typedef struct CarStatus
{
    car_light light_s;
    car_ac ac_s;
    Car_Timer timer;
    car_wiper wiper_s;
    car_drive drive_s;
}CarStatus;


void init_car_status(CarStatus *state);
int check_timer_expire(clock_t* timer, clock_t interval);

#endif