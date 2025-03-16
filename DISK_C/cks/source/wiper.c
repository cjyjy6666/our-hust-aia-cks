#include"allfunc.h"

void wiper(CarStatus *state,int *puge)
{
	mouse_off(&mouse);
    draw_wiper_page();
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
        if (mouse_press(100,190,200,260) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.auto_w^= 1;
        }
        if (mouse_press(100,290,200,360) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.once^= 1;
        }
        if (mouse_press(433,190,533,260) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.fast^= 1;
        }
        if (mouse_press(433,290,533,360) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.slow^= 1;
        }
    }
}

void draw_wiper_page()
{
    bar2(100,190,200,260,0xFFFFFF);
	bar2(100,290,200,360,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
	puthz(130, 215, "自动",24,30,0xFFFFFF);//auto
    puthz(130, 315, "一刮",24,30,0xFFFFFF);//wipe once
    puthz(463, 215, "高速",24,30,0xFFFFFF); //fast
    puthz(463, 315, "低速",24,30,0xFFFFFF); //slow
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}