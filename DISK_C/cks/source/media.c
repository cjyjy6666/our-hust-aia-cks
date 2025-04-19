#include"allfunc.h"

void media(CarStatus *state,int *puge)
{
	mouse_off(&mouse);
    draw_media_page();
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
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge=9;
			break;
		}
        if (mouse_press(100,290,200,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge=10;
			break;
		}
        if (mouse_press(433,190,533,260) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge=11;
			break;
		}
        if (mouse_press(433,290,533,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge=12;
			break;
		}
    }
}

void draw_media_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
    
    bar2(100,190,200,260,0xFFFFFF);
	bar2(100,290,200,360,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
    puthz(130, 215, "≤¶∫≈",24,30,0xFFFFFF);//phone
    puthz(130, 315, "Õ®—∂",24,30,0xFFFFFF);//contact
    puthz(463, 215, "“Ù¿÷",24,30,0xFFFFFF); //music
    puthz(463, 315, "“ÙœÏ",24,30,0xFFFFFF); //sound
}