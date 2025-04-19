#include"allfunc.h"
#define PI 3.1415926
void show_all(CarStatus *state)
{
	show_light(state);
	show_ac(state);
	show_wiper(state);
	show_drive(state);
	show_phone(state);
	show_music(state);
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
	xs=(int)(829-130*cos(state->drive_s.angle_s*PI/180));
    ys=(int)(400-130*sin(state->drive_s.angle_s*PI/180));
    xs1=(int)(829-50*cos(state->drive_s.angle_s*PI/180));
    ys1=(int)(400-50*sin(state->drive_s.angle_s*PI/180));
	xn=(int)(829-130*cos(state->drive_s.angle_n*PI/180));
    yn=(int)(194-130*sin(state->drive_s.angle_n*PI/180));
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

void show_phone(CarStatus *state)
{
	char call_str[10]={'\0'};
	if(state->media_s.on_call)
	{
		if(check_timer_expire(&(state->timer.call_time), CLOCKS_PER_SEC))
		{
			state->media_s.call_second++;
			bar1(660,700,860,748,0x0000);
			sprintf(call_str,"Í¨»°ÖÐ:%dÃë",state->media_s.call_second);
			prt_hz24_asc32(660,700,call_str,0xFC44,"HZK\\Hzk24f");
		}
	}
	else
	bar1(660,700,860,748,0x0000);//660,600 before change
}
void show_music(CarStatus *state)
{
	char mus_name[15];
	char mus_str[30];
	int i,newline_pos;
	static int sec=75;
	static int cur_music=-1;
	static FILE *fp;
	static int file_init=0;
	static int TOTLE=-1;

	if(TOTLE==-1)
	{
		TOTLE=count_music();
	}
	//accessing music name
	if(!file_init)
	{
		fp=fopen("data\\music.txt","r");
		if(fp==NULL)
		{
			printf("open music.txt error\n");
			return;
		}
		file_init=1;
	}
	else
		rewind(fp);
	for(i=0;i<state->media_s.music+1;i++)
	{
		if(fgets(mus_name,sizeof(mus_name),fp)==NULL)
		{
			printf("read music.txt error\n");
			//fclose(fp);
			return;
		}
	}
	//fclose(fp);
	//delete \n
	newline_pos=-1;
	for(i=0;i<sizeof(mus_name)+1;i++)
	{
		if(mus_name[i]=='\n')
		{
			newline_pos=i;
			break;
		}
	}
	if(newline_pos!=-1)
	{
		mus_name[newline_pos]='\0';//replace \n with \0
	}
	else
	{
		mus_name[14]='\0';//if no \n
	}

	//display music name and time
	if(state->media_s.music!=-1)
	{
		if(cur_music!=state->media_s.music)
		{
			sec=75;
			cur_music=state->media_s.music;
		}
		if(check_timer_expire(&(state->timer.music_time), CLOCKS_PER_SEC))
		{
			sec--;
			bar1(660,650,920,700,0x0000);
			sprintf(mus_str,"%s:%d:%d",mus_name,sec/60,sec%60);
			prt_hz24_asc32(660,650,mus_str,0xFC44,"HZK\\Hzk24f");
		}
		if(sec<=0)
		{
			sec=75;
			switch(state->media_s.mus_ord)
			{
				case 0:
					state->media_s.music=(state->media_s.music+1)%TOTLE;
					break;
				case 1:
					//randomize();
					state->media_s.music=random(TOTLE);
					break;
				case 2:
					break;
			}
		}
	}
	else if(cur_music!=-1)
		bar1(660,650,920,700,0x0000);
	if(state->media_s.music==-1&&fp!=NULL)
	{
		fclose(fp);
		file_init=0;
	}
}