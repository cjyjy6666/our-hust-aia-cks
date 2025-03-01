#include"allfunc.h"

void show_all()
{
    CarStatus *status = get_car_status();
    show_light(status->light_status);
}

void show_light(struct car_light light_status)
{
    light_blink();
    if(light_status.far_light)
        Readbmp64k(670,500,"bmp\\far.bmp");
    else
        bar1(670,500,704,522,0x0000);
        
    if(light_status.near_light)
        Readbmp64k(670,532,"bmp\\near.bmp");
    else
        bar1(670,532,704,556,0x0000);
    if(light_status.fog)
	{
		Readbmp64k(670,569,"bmp\\fog1.bmp");
		Readbmp64k(704,566,"bmp\\fog2.bmp");
	}    
	else
	{
		bar1(670,569,704,591,0x0000);
		bar1(704,566,738,591,0x0000);
	}
	if(light_status.left_blink_state)
		Readbmp64k(670,452,"bmp\\left.bmp");
	else
		bar1(670,452,704,494,0x0000);
	if(light_status.right_blink_state)
		Readbmp64k(956,452,"bmp\\right.bmp");
	else
		bar1(956,452,990,493,0x0000);
}

void light_blink()//转向灯闪烁函数
{
    CarStatus *status = get_car_status();

	if(check_timer_expire(&status->timer.light_time, CLOCKS_PER_SEC/2))
	{
		if(status->light_status.left)
            status->light_status.left_blink_state ^= 1;
        else
            status->light_status.left_blink_state = 0;
            
        if(status->light_status.right)
            status->light_status.right_blink_state ^= 1;
        else
            status->light_status.right_blink_state = 0;
	}
}