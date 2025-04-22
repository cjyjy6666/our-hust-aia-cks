#include"allfunc.h"
//Chinese in UTF-8 in this file.
//CarStatus global_status = {0};  // 保持静态初始化为零

// 初始化函数
void init_car_status(CarStatus *state) 
{
    FILE *fp;
    randomize();
    state->ac_s.current_temp=random(36);
    state->ac_s.cur_t=state->ac_s.current_temp;
    state->wiper_s.rain=random(3);
    fp=fopen("data\\temp.dat","rb+");
    fread(&state->ac_s.target_temp,sizeof(int),1,fp);
    fclose(fp);
    state->drive_s.angle_s =20.0;
    state->drive_s.angle_n =20.0;
    state->media_s.music=-1;
    randomize();
    state->media_s.initialized=0;
    state->media_s.first_time=1;
    state->chair_s.x1=170;
    state->chair_s.y1=163;
    state->chair_s.x2=470;
    state->chair_s.y2=200;
}

/*CarStatus* get_car_status(void)
{
    return &global_status;
}*/
/*这是车辆状态接口调用函数，
其它文件中可以用CarStatus* status = get_car_status();
来获取统一的全局车辆状态信息。*/

int check_timer_expire(clock_t* timer, clock_t interval) 
{
    clock_t now = clock();
    if(now -*timer > interval) 
    {
        *timer = now;
        return 1;
    }
    return 0;
}//通用的计时检查函数