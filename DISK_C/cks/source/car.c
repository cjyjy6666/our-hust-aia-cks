#include"allfunc.h"
//Chinese in UTF-8 in this file.
CarStatus global_status = {0};  // 保持静态初始化为零

// 初始化函数
/*void init_car_status() 
{
    //global_status.timer.light_time = 0;
    // 其他需要运行时初始化的字段
}*/

CarStatus* get_car_status(void)
{
    return &global_status;
}
/*这是车辆状态接口调用函数，
其它文件中可以用CarStatus* status = get_car_status();
来获取统一的全局车辆状态信息。*/

int check_timer_expire(clock_t *timer, clock_t interval) 
{
    clock_t now = clock();
    if(now - *timer > interval) 
    {
        *timer = now;
        return 1;
    }
    return 0;
}//通用的计时检查函数