#include"allfunc.h"
#define PI 3.1415926
void show_all(CarStatus *state)
{
	show_light(state);
	show_ac(state);
	show_wiper(state);
	show_drive(state);
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

void light_blink(CarStatus *state)
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

void show_ac(CarStatus *state)
{
	char cur_temp[5]={'\0'};
	itoa(state->ac_s.current_temp,cur_temp,10);
	sprintf(cur_temp,"%d¡æ",state->ac_s.current_temp);
	prt_hz24_asc32(40,667,cur_temp,0xFC44,"HZK\\Hzk24f");
	if(state->ac_s.circulate)
		Readbmp64k(710,452,"bmp\\accir.bmp");
	else
		bar1(710,452,744,472,0x0000);
	if(state->ac_s.fresh_air)
		Readbmp64k(710,532,"bmp\\acair.bmp");
	else
		bar1(710,532,744,549,0x0000);
	if(state->ac_s.defog)
		Readbmp64k(710,500,"bmp\\acfog.bmp");
	else
		bar1(710,500,744,526,0x0000);

	temp_change(state);
}

void show_wiper(CarStatus *state)
{
	if(state->wiper_s.cur_wip==2)
		Readbmp64k(930,700,"bmp\\w1.bmp");
	else
		bar1(930,700,990,747,0x0000);
	if(state->wiper_s.cur_wip==1)
		Readbmp64k(930,650,"bmp\\w2.bmp");
	else
		bar1(930,650,990,694,0x0000);
}

void show_drive(CarStatus *state)
{
	int xs,ys,xs1,ys1,xn,yn,xn1,yn1;
	xs=(int)(829-150*cos(state->drive_s.angle_s*PI/180));
    ys=(int)(400-150*sin(state->drive_s.angle_s*PI/180));
    xs1=(int)(829-50*cos(state->drive_s.angle_s*PI/180));
    ys1=(int)(400-50*sin(state->drive_s.angle_s*PI/180));
	xn=(int)(829-150*cos(state->drive_s.angle_n*PI/180));
    yn=(int)(194-150*sin(state->drive_s.angle_n*PI/180));
    xn1=(int)(829-50*cos(state->drive_s.angle_n*PI/180));
    yn1=(int)(194-50*sin(state->drive_s.angle_n*PI/180));
	Line2(xs1,ys1,xs,ys,0xF800);
	Line2(xn1,yn1,xn,yn,0xF800);
	if(state->drive_s.forward==1&&state->drive_s.sport==0&&state->drive_s.comfort==0&&state->drive_s.view==0)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'D',0xF800);
		needle_s(state,100);
		if(!state->drive_s.once_f)
		{
			if(n_change(state))
			state->drive_s.once_f=1;
		}
	}
	if(state->drive_s.back==1)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'R',0xF800);
		needle_s(state,60);
		if(!state->drive_s.once_b)
		{
			if(n_change(state))
			state->drive_s.once_b=1;
		}
	}
	if(state->drive_s.park==1)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'P',0xF800);
		needle_s(state,20);
		if(!state->drive_s.once_p)
		{
			if(n_change(state))
			state->drive_s.once_p=1;
		}
	}
	if(state->drive_s.sport==1)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'S',0xF800);
		needle_s(state,150);
		if(!state->drive_s.once_s)
		{
			if(n_change(state))
			state->drive_s.once_s=1;
		}
	}
	if(state->drive_s.comfort==1)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'D',0xF800);
		needle_s(state,80);
	}
	if(state->drive_s.view==1)
	{
		//bar1(800,460,840,500,0x0000);
		Put_Asc16_Size(800,460,2,2,'D',0xF800);
		needle_s(state,40);
	}
}