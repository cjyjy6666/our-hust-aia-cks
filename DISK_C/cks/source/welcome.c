#include"allfunc.h"

void welcome(CarStatus *state,int* puge)
{
	mouse_off(&mouse);

	draw_welcome();



	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);

		if (mouse.x >= 401 && mouse.x <= 594 && mouse.y >= 416 && mouse.y <= 579 && !state->button_s.welcome) {
			state->button_s.welcome=1;
			mouse_off(&mouse);
			Circlefill(490,504,120,0x8410);
			Circlefill(490, 504, 108, 0xE60000);
	Circlefill(490, 504, 100, 0x8410);
	Line_Thick(490, 375, 490, 463, 5, 0xE60000);
			mouse_on(mouse);
		} else if (state->button_s.welcome && (mouse.x < 401 || mouse.x > 594 || mouse.y < 416 || mouse.y > 579)) {
			state->button_s.welcome = 0;
			mouse_off(&mouse);
			Circlefill(490,504,130,0xC618);
			Circlefill(490, 504, 108, 0xE60000);
	Circlefill(490, 504, 100, 0xC618);
	Line_Thick(490, 375, 490, 463, 5, 0xE60000);
			mouse_on(mouse);
		}

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
	Circlefill(490, 504, 130, 0xC618);
	Circlefill(490, 504, 108, 0xE60000);
	Circlefill(490, 504, 100, 0xC618);
	Line_Thick(490, 375, 490, 463, 5, 0xE60000);
	puthz(410, 200, "按下启动", 48, 50, 0xE60000);

}