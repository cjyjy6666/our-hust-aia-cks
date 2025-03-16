#include"allfunc.h"

void ac(CarStatus *state,int *puge)
{
	mouse_off(&mouse);
    draw_ac_page();
    mouse_on(mouse);

    while(1)
    {
        show_all(state);
		temp(state);
		mouse_show(&mouse);
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;
			break;
		}
        if(mouse_press(100,90,200,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 1)
                state->ac_s.ac_state = 0;
            else
            {
                state->ac_s.ac_state = 1;
                //state->ac_s.target_temp = 26;
            }
            
        }
        if(mouse_press(100,190,200,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 2)
                state->ac_s.ac_state = 0;
            else
            {
            state->ac_s.ac_state = 2;
            state->ac_s.target_temp = state->ac_s.current_temp-1;
            }
        }
        if(mouse_press(100,290,200,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 3)
                state->ac_s.ac_state = 0;
            else
            {
                state->ac_s.ac_state = 3;
                state->ac_s.target_temp = state->ac_s.current_temp+1;
            }
        }
        if(mouse_press(433,90,533,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.circulate ^= 1;
        }
        if(mouse_press(433,190,533,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.fresh_air ^= 1;
        }
        if(mouse_press(433,290,533,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.defog ^= 1;
        }
    }
}

void draw_ac_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
    
    bar2(100,90,200,160,0xFFFFFF);
	bar2(100,190,200,260,0xFFFFFF);
    bar2(100,290,200,360,0xFFFFFF);
    bar2(433,90,533,160,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
    bar2(433,290,533,360,0xFFFFFF);

    puthz(130, 115, "自动",24,30,0xFFFFFF);//auto
    puthz(130, 215, "制冷",24,30,0xFFFFFF);//cold
    puthz(130, 315, "暖风",24,30,0xFFFFFF);//heating
    puthz(463, 115, "循环",24,30,0xFFFFFF);//circulation
    puthz(463, 215, "通风",24,30,0xFFFFFF); //air_refreshing
    puthz(463, 315, "除雾",24,30,0xFFFFFF);//defoging
}

void temp(CarStatus *state)
{
    char tag_temp[5]={'\0'};
    FILE *fp;
    prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
    if(state->ac_s.ac_state == 1)
    {
        if(state->ac_s.target_temp<=35&&state->ac_s.target_temp>=0)
        {
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.target_temp<35)//temp+
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
                fp=fopen("data\\temp.dat","wb+");
                fwrite(&state->ac_s.target_temp,sizeof(int),1,fp);
                fclose(fp);
            }
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.target_temp>0)//temp-
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
                fp=fopen("data\\temp.dat","wb+");
                fwrite(&state->ac_s.target_temp,sizeof(int),1,fp);
                fclose(fp);
            } 
        }
    }
    if(state->ac_s.ac_state == 2)
    {
        
        if(state->ac_s.target_temp>=0&&state->ac_s.current_temp>=state->ac_s.target_temp)
        {
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.cur_t>state->ac_s.target_temp)//temp+
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.target_temp>0)//temp-
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
        } 
    }
    if(state->ac_s.ac_state == 3)
    {
        
        if(state->ac_s.target_temp<=35&&state->ac_s.current_temp<=state->ac_s.target_temp)
        {
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.target_temp<35)//temp+
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.cur_t<state->ac_s.target_temp)//temp-
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
        } 
    }
}

void temp_change(CarStatus *state)
{
    if(state->ac_s.ac_state)
    {
        if(check_timer_expire(&(state->timer.ac_time),4*CLOCKS_PER_SEC)) 
        {
            if(state->ac_s.current_temp < state->ac_s.target_temp) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp++;
            } 
            else if(state->ac_s.current_temp > state->ac_s.target_temp) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp--;
            }
        }
    }
    else
    {
        if(check_timer_expire(&(state->timer.ac_time),4*CLOCKS_PER_SEC)) 
        {
            if(state->ac_s.current_temp < state->ac_s.cur_t) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp++;
            } 
            else if(state->ac_s.current_temp > state->ac_s.cur_t) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp--;
            }
        }
    }
}