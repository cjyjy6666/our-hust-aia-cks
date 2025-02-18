#include"allfunc.h"

void welcome(int* puge)
{
	mouse_off(&mouse);

	draw_welcome();



	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);

		if (mouse_press(401, 416, 594, 579) == 1)
		{
			*puge = 2;
			break;
		}

	}
}


void draw_welcome()
{
	Readbmp64k(0, 0, "bmp\\111.bmp");
	puthz(410, 80, "欢迎使用", 48, 50, 0x000000);
	puthz(360, 140, "无人驾驶汽车", 48, 50, 0x000000);
	Circle(490, 504, 100, 0xE60000);
	Circle(490, 504, 101, 0xE60000);
	Circle(490, 504, 102, 0xE60000);
	Circle(490, 504, 103, 0xE60000);
	Circle(490, 504, 104, 0xE60000);
	Circle(490, 504, 105, 0xE60000);
	Circle(490, 504, 106, 0xE60000);
	Circle(490, 504, 107, 0xE60000);
	Circle(490, 504, 108, 0xE60000);
	Line_Thick(490, 355, 490, 463, 5, 0xE60000);
	puthz(410, 200, "按下启动", 48, 50, 0xE60000);

}