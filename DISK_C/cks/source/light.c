#include"allfunc.h"

void light(int *puge)
{
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while (1)
	{
		mouse_show(&mouse);
		if (mouse_press(80, 70, 220, 200) == 1)
		{
			*puge = 3;
			break;
		}
	}

}

void draw_light_page()
{
    bar1(0,0,633,630,0x000000);
}