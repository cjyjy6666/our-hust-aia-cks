#include"allfunc.h"

void mainpage(int *puge)
{
	mouse_off(&mouse);

	draw_mainpage();



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

//然后从main函数开始做的
void draw_mainpage()
{
	bar1(0, 0, 1024, 768,0xFFFFFF);
	Line_Thick(633, 0, 633, 768, 1, 0x000000);
	Line_Thick(0, 630, 633, 630, 1, 0x000000);
	Circle(829, 194, 180, 0x000000);
	Circle(829, 194, 179, 0x000000);
	Circle(829, 194, 178, 0x000000);
	Circle(829, 194, 177, 0x000000);
	Circle(829, 194, 176, 0x000000);
	bar1(640, 195, 1024, 768, 0xFFFFFF);
	Line_Thick(649, 194, 1009, 194, 1, 0x000000);
	Circle(829, 400, 180, 0x000000);
	Circle(829, 400, 179, 0x000000);
	Circle(829, 400, 178, 0x000000);
	Circle(829, 400, 177, 0x000000);
	Circle(829, 400, 176, 0x000000);
	bar1(640, 400, 1024,768, 0xFFFFFF);
	Line_Thick(649, 400, 1009, 400, 1, 0x000000);
	bar1(660, 450, 1000, 748, 0x000000);
	draw_botton(80, 70, 220, 200, 0x00FF, 0xDDDD);
	draw_botton(80, 250, 220, 380, 0x00FF, 0xDDDD);
	draw_botton(80, 440, 220, 570, 0x00FF, 0xDDDD);
	draw_botton(380, 70, 520, 200, 0x00FF, 0xDDDD);
	draw_botton(380, 250, 520, 380, 0x00FF, 0xDDDD);
	draw_botton(380, 440, 520, 570, 0x00FF, 0xDDDD);
	puthz(110,119,"灯光",32,40,0xFFFFFF);
}


void draw_botton(int x1, int y1, int x2, int y2, int Cowercolor, int Bordercolor)
{
	Cirbar(x1, y1, x2, y2, Bordercolor);
	Cirbar(x1, y1, x2, y2, Cowercolor);
}