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
	draw_botton(100,190,200,260,0x00FF,0x0000);
	draw_botton(100,290,200,360,0x00FF,0x0000);
	draw_botton(266,440,366,510,0x00FF,0x0000);
	draw_botton(433,190,533,260,0x00FF,0x0000);
	draw_botton(433,290,533,360,0x00FF,0x0000);
	//双闪（不对）
	Line2(316,63,266,150,0xF800);
	Line2(316,63,366,150,0xF800);
	Line2(266,150,366,150,0xF800);
	Line2(316,53,275,145,0xF800);
	Line2(316,53,357,145,0xF800);
	Line2(275,145,357,145,0xF800);
}