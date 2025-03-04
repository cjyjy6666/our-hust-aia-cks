#include"allfunc.h"


void auto(int *put)
{
    mouse_off(&mouse);

	draw_auto();



	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);

		
	}
}

void draw_auto()
{
    bar1(0, 0, 1024, 768,0xFFFFFF);
    Line_Thick(0,250,1024,250, 0x000000);
    
}

