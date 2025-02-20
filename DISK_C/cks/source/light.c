#include"allfunc.h"



void light(int *puge)
{
	struct car_light light_status={0,0,0,0,0};/*结构体在light.h中定义*/
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while (1)
	{
		show_light(light_status);
		mouse_show(&mouse);
		if (mouse_press(100,190,200,260) == 1)
		{
			light_status.right=light_status.right?0:1;
		}
		if (mouse_press(100,290,200,360) == 1)
		{
			light_status.left=light_status.left?0:1;
		}
		if (mouse_press(266,440,366,510) == 1)
		{
			light_status.fog=light_status.fog?0:1;
		}
		if (mouse_press(433,190,533,260) == 1)
		{
			light_status.near_light=light_status.near_light?0:1;
		}
		if (mouse_press(433,290,533,360) == 1)
		{
			light_status.far_light=light_status.far_light?0:1;	
		}
		if (mouse_press(266,63,366,150) == 1)
		{
			light_status.left=light_status.left?0:1;
			light_status.right=light_status.right?0:1;
		}
		if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;
			break;
		}
	}

}

/*	留了两个小问题
没有写双闪和左（右）转同时按下的情形
双闪按钮的detect写的的矩形范围，可以改进成三角形区域
*/

void draw_light_page()
{
    bar1(0,0,633,630,0x000000);
	draw_botton(100,190,200,260,0x00FF,0x0000);
	draw_botton(100,290,200,360,0x00FF,0x0000);
	draw_botton(266,440,366,510,0x00FF,0x0000);
	draw_botton(433,190,533,260,0x00FF,0x0000);
	draw_botton(433,290,533,360,0x00FF,0x0000);
	//双闪
	Line2(316,63,266,150,0xF800);
	Line2(316,63,366,150,0xF800);
	Line2(266,150,366,150,0xF800);
	Line2(316,73,275,145,0xF800);
	Line2(316,73,357,145,0xF800);
	Line2(275,145,357,145,0xF800);
	Put_Asc16_Size(308, 100, 2, 2, '!', 0xF800);
	puthz(130, 215, "右转",24,30,0xFFFFFF);
    puthz(130, 315, "左转",24,30,0xFFFFFF);
    puthz(296, 465, "雾灯",24,30,0xFFFFFF);
    puthz(463, 215, "近光",24,30,0xFFFFFF); 
    puthz(463, 315, "远光",24,30,0xFFFFFF); 
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}

void show_light(struct car_light light_status)
{
	
}