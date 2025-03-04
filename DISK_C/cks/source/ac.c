#include"allfunc.h"

void ac(int *puge)
{
    CarStatus *status = get_car_status();
	uint8_t new_state;
	mouse_off(&mouse);
    draw_ac_page();
    mouse_on(mouse);
}

void draw_ac_page()
{
    bar1(0,0,633,630,0xFFFFFF);
    Line2(603,600,633,600,0x000000);
	Line2(603,600,603,630,0x000000);
	Line2(603,600,633,630,0x000000);
	Line2(633,600,603,630,0x000000);//ÍË³ö°´Å¥
    

}