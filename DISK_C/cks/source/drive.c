#include"allfunc.h"
#define PI 3.1415926537
void drive(CarStatus *state,int *puge)
{
    mouse_off(&mouse);
    draw_drive_page();
    mouse_on(mouse);
    while(1)
    {
        show_all(state);	
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
            state->drive_s.forward ^= 1;
        }
        if(mouse_press(100,190,200,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->drive_s.back ^= 1;
        }
        if(mouse_press(100,290,200,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->drive_s.park ^= 1;
        }
        if(mouse_press(433,90,533,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->drive_s.sport ^= 1;
        }
        if(mouse_press(433,190,533,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->drive_s.comfort ^= 1;
        }
        if(mouse_press(433,290,533,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);	
            state->drive_s.view ^= 1;
        }
    }
}

void draw_drive_page()
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

    puthz(130, 115, "前进",24,30,0xFFFFFF);//forward
    puthz(130, 215, "后退",24,30,0xFFFFFF);//back
    puthz(130, 315, "泊车",24,30,0xFFFFFF);//park
    puthz(463, 115, "运动",24,30,0xFFFFFF);//sport
    puthz(463, 215, "舒适",24,30,0xFFFFFF); //comfort
    puthz(463, 315, "观光",24,30,0xFFFFFF);//view
}

int needle_s(CarStatus *state,double s)//from 20~160
{
    int x,y,x1,y1;
    if(state->drive_s.angle_s<s)
    {
        x=(int)(829-150*cos(state->drive_s.angle_s*PI/180));
        y=(int)(400-150*sin(state->drive_s.angle_s*PI/180));
        x1=(int)(829-50*cos(state->drive_s.angle_s*PI/180));
        y1=(int)(400-50*sin(state->drive_s.angle_s*PI/180));
        if((check_timer_expire(&(state->timer.drive_time_s),CLOCKS_PER_SEC/40))&&(fabs(state->drive_s.angle_s-s)>3))
        {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_s+=4;
            Line2(x1,y1,x,y,0xFFFFFF);
        }
        if(fabs(state->drive_s.angle_s-s)<5)
        {
            state->drive_s.angle_s=s;
            return 1;
        }
        return 0;
    }
    if(state->drive_s.angle_s>s)
    {
        x=(int)(829-150*cos(state->drive_s.angle_s*PI/180));
        y=(int)(400-150*sin(state->drive_s.angle_s*PI/180));
        x1=(int)(829-50*cos(state->drive_s.angle_s*PI/180));
        y1=(int)(400-50*sin(state->drive_s.angle_s*PI/180));
        if((check_timer_expire(&(state->timer.drive_time_s),CLOCKS_PER_SEC/40))&&(fabs(state->drive_s.angle_s-s)>3))
        {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_s-=4;
            Line2(x1,y1,x,y,0xFFFFFF);
        }
        if(fabs(state->drive_s.angle_s-s)<5)
        {
            state->drive_s.angle_s=s;
            return 1;
        }
        return 0;
    }
}

int needle_n(CarStatus *state,double s)//from 20~160
{
    int x,y,x1,y1;
    if(state->drive_s.angle_n<s)
    {
        x=(int)(829-150*cos(state->drive_s.angle_n*PI/180));
        y=(int)(194-150*sin(state->drive_s.angle_n*PI/180));
        x1=(int)(829-50*cos(state->drive_s.angle_n*PI/180));
        y1=(int)(194-50*sin(state->drive_s.angle_n*PI/180));
        if((check_timer_expire(&(state->timer.drive_time_n),CLOCKS_PER_SEC/40))&&(fabs(state->drive_s.angle_n-s)>3))
        {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_n+=4;
            Line2(x1,y1,x,y,0xFFFFFF);
        }
        if(fabs(state->drive_s.angle_n-s)<5)
        {
            state->drive_s.angle_n=s;
            return 1;
        }
        return 0;
    }
    if(state->drive_s.angle_n>s)
    {
        x=(int)(829-150*cos(state->drive_s.angle_n*PI/180));
        y=(int)(194-150*sin(state->drive_s.angle_n*PI/180));
        x1=(int)(829-50*cos(state->drive_s.angle_n*PI/180));
        y1=(int)(194-50*sin(state->drive_s.angle_n*PI/180));
        if((check_timer_expire(&(state->timer.drive_time_n),CLOCKS_PER_SEC/40))&&(fabs(state->drive_s.angle_n-s)>3))
        {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_n-=4;
            Line2(x1,y1,x,y,0xFFFFFF);
        }
        if(fabs(state->drive_s.angle_n-s)<5)
        {
            state->drive_s.angle_n=s;
            return 1;
        }
        return 0;
    }
}