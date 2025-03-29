#include"allfunc.h"

void contact(CarStatus *state,int *puge)
{
	mouse_off(&mouse);
    draw_contact_page();
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

void draw_contact_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);

    bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
    puthz(463, 215, "²¦´ò",24,30,0xFFFFFF); //call
    puthz(463, 315, "É¾³ý",24,30,0xFFFFFF); //delete
}