#include"allfunc.h"

void ac(int *puge)
{
    CarStatus *status = get_car_status();
	uint8_t new_state;
	mouse_off(&mouse);
    draw_ac_page();
    mouse_on(mouse);

    while(1)
    {
        show_all();
		
		mouse_show(&mouse);
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;
			break;
		}
    }
}

void draw_ac_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);//退出按钮
    
    bar2(100,90,200,160,0xFFFFFF);
	bar2(100,190,200,260,0xFFFFFF);
    bar2(100,290,200,360,0xFFFFFF);
    bar2(433,90,533,160,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
    bar2(433,290,533,360,0xFFFFFF);

    puthz(130, 115, "自动",24,30,0xFFFFFF);
    puthz(130, 215, "制冷",24,30,0xFFFFFF);
    puthz(130, 315, "暖风",24,30,0xFFFFFF);
    puthz(463, 115, "循环",24,30,0xFFFFFF);
    puthz(463, 215, "通风",24,30,0xFFFFFF); 
    puthz(463, 315, "除雾",24,30,0xFFFFFF);
}