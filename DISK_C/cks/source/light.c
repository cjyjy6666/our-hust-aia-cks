#include"allfunc.h"



void light(int *puge)
{
	struct car_light light_status={0,0,0,0,0,0,0};/*�ṹ����light.h�ж���*/
	clock_t last_blink=0,last_blink1=0;//����ʱ������������ڵƵ���˸
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while (1)
	{
		if(light_status.left)
		{
			if(clock()-last_blink>CLOCKS_PER_SEC/2)//1sʱ����
			{
			light_status.left_blink_state^=1;
			last_blink=clock();
			}
		}
		else
			light_status.left_blink_state=0;
		if(light_status.right)
		{
			if(clock()-last_blink1>CLOCKS_PER_SEC/2)//1sʱ����
			{
			light_status.right_blink_state^=1;
			last_blink1=clock();
			}
		}
		else
			light_status.right_blink_state=0;
		show_light(light_status);
		mouse_show(&mouse);
        
        // �޸�������߼��������ͷż�����
        if (mouse_press(433,190,533,260) == 1) {
            // �ȴ�����ͷ�
            do {
                MouseGet(&mouse);      // ������ȡ����״̬
                mouse_show(&mouse);   // ���������ʾ����
            } while ((mouse.key & 1) == 1);  // ������״̬λ
            
            light_status.near_light ^= 1;
        }

        if (mouse_press(433,290,533,360) == 1) {
            // �ȴ�����ͷ�
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            light_status.far_light ^= 1;    
        }

		if (mouse_press(100,190,200,260) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            light_status.right^=1;
			light_status.right_blink_state=light_status.right;
			last_blink1=clock();//���ü�ʱ��
		}
		if (mouse_press(100,290,200,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            light_status.left^=1;
			light_status.left_blink_state=light_status.left;
			last_blink=clock();//���ü�ʱ��
		}
		if (mouse_press(266,440,366,510) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            light_status.fog ^= 1;
		}
		if (mouse_press(266,63,366,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
			light_status.right^=1;
			light_status.right_blink_state=light_status.right;
			last_blink1=clock();//���ü�ʱ��
			light_status.left^=1;
			light_status.left_blink_state=light_status.left;
			last_blink=clock();//���ü�ʱ��
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

/*���⣬������滹����ʱ�䣬���Լ����Զ����
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
    if(light_status.far_light)
        Readbmp64k(670,500,"bmp\\far.bmp");
    else
        bar1(670,500,704,522,0x0000);
        
    if(light_status.near_light)
        Readbmp64k(670,532,"bmp\\near.bmp");
    else
        bar1(670,532,704,556,0x0000);
    if(light_status.fog)
	{
		Readbmp64k(670,569,"bmp\\fog1.bmp");
		Readbmp64k(704,566,"bmp\\fog2.bmp");
	}    
	else
	{
		bar1(670,569,704,591,0x0000);
		bar1(704,566,738,591,0x0000);
	}
	if(light_status.left_blink_state)
		Readbmp64k(670,452,"bmp\\left.bmp");
	else
		bar1(670,452,704,494,0x0000);
	if(light_status.right_blink_state)
		Readbmp64k(956,452,"bmp\\right.bmp");
	else
		bar1(956,452,990,493,0x0000);
}


