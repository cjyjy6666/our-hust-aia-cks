#include"allfunc.h"

void show_all(CarStatus *state)
{
	show_light(state);
}


void show_light(CarStatus *state)
{
    light_blink(state);
    if(state->light_s.far_light)
        Readbmp64k(670,500,"bmp\\far.bmp");
    else
        bar1(670,500,704,522,0x0000);
        
    if(state->light_s.near_light)
        Readbmp64k(670,532,"bmp\\near.bmp");
    else
        bar1(670,532,704,556,0x0000);
    if(state->light_s.fog)
	{
		Readbmp64k(670,569,"bmp\\fog1.bmp");
		Readbmp64k(704,566,"bmp\\fog2.bmp");
	}    
	else
	{
		bar1(670,569,704,591,0x0000);
		bar1(704,566,738,591,0x0000);
	}
	if(state->light_s.left_blink_state)
		Readbmp64k(670,452,"bmp\\left.bmp");
	else
		bar1(670,452,704,494,0x0000);
	if(state->light_s.right_blink_state)
		Readbmp64k(956,452,"bmp\\right.bmp");
	else
		bar1(956,452,990,493,0x0000);
}

void light_blink(CarStatus *state)//转向灯闪烁函数
{
    //CarStatus *status = get_car_status();

	if(check_timer_expire(&(state->timer.light_time), CLOCKS_PER_SEC/2))
	{
		if(state->light_s.left)
            state->light_s.left_blink_state ^= 1;
        else
            state->light_s.left_blink_state = 0;
            
        if(state->light_s.right)
            state->light_s.right_blink_state ^= 1;
        else
            state->light_s.right_blink_state = 0;
	}
}