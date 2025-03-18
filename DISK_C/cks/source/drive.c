#include"allfunc.h"

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
    puthz(130, 315, "泊车",24,30,0xFFFFFF);//parking
    puthz(463, 115, "运动",24,30,0xFFFFFF);//sports
    puthz(463, 215, "舒适",24,30,0xFFFFFF); //comofort
    puthz(463, 315, "观光",24,30,0xFFFFFF);//viewing
}