#include"allfunc.h"



void light(int *puge)
{
	struct car_light light_status={0,0,0,0,0};/*�ṹ����light.h�ж���*/
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

/*	��������С����
û��д˫�������ң�תͬʱ���µ�����
˫����ť��detectд�ĵľ��η�Χ�����ԸĽ�������������
*/

/*���⣬������滹����ʱ��������Լ����Զ����
*/

void draw_light_page()
{
    bar1(0,0,633,630,0x000000);
	draw_botton(100,190,200,260,0x00FF,0x0000);
	draw_botton(100,290,200,360,0x00FF,0x0000);
	draw_botton(266,440,366,510,0x00FF,0x0000);
	draw_botton(433,190,533,260,0x00FF,0x0000);
	draw_botton(433,290,533,360,0x00FF,0x0000);
	//˫��  ����û����BMP.H�ﻭ�����εĺ������Ⱦ������ü���ֱ�ߴպ�һ��
	Line2(316,63,266,150,0xF800);
	Line2(316,63,366,150,0xF800);
	Line2(266,150,366,150,0xF800);
	Line2(316,73,275,145,0xF800);
	Line2(316,73,357,145,0xF800);
	Line2(275,145,357,145,0xF800);
	Put_Asc16_Size(308, 100, 2, 2, '!', 0xF800);
	puthz(130, 215, "��ת",24,30,0xFFFFFF);
    puthz(130, 315, "��ת",24,30,0xFFFFFF);
    puthz(296, 465, "���",24,30,0xFFFFFF);
    puthz(463, 215, "����",24,30,0xFFFFFF); 
    puthz(463, 315, "Զ��",24,30,0xFFFFFF); 
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}

void show_light(struct car_light light_status)
{
	if(light_status.right==1)
	show_right();
	if(light_status.left==1)
	show_left();
	if(light_status.fog==1)
	show_fog();
	if(light_status.near_light==1)
	show_near();
	if(light_status.far_light==1)
	show_far();

}

void show_right()
{

}

void show_left()
{

}

void show_fog()
{

}

void show_near()
{
	
}

void show_far()
{

}

