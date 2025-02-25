#include"allfunc.h"



void light(int *puge)
{
	struct car_light light_status={0,0,0,0,0,0,0};/*结构体在light.h中定义*/
	clock_t last_blink=0,last_blink1=0;//定义时间戳变量，用于灯的闪烁
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while (1)
	{
		if(light_status.left)
		{
			if(clock()-last_blink>CLOCKS_PER_SEC/2)//1s时间间隔
			{
			light_status.left_blink_state^=1;
			last_blink=clock();
			}
		}
		else
			light_status.left_blink_state=0;
		if(light_status.right)
		{
			if(clock()-last_blink1>CLOCKS_PER_SEC/2)//1s时间间隔
			{
			light_status.right_blink_state^=1;
			last_blink1=clock();
			}
		}
		else
			light_status.right_blink_state=0;
		show_light(light_status);
		mouse_show(&mouse);
        
        // 修改鼠标检测逻辑：增加释放检测防抖
        if (mouse_press(433,190,533,260) == 1) {
            // 等待左键释放
            do {
                MouseGet(&mouse);      // 持续获取最新状态
                mouse_show(&mouse);   // 保持鼠标显示更新
            } while ((mouse.key & 1) == 1);  // 检查左键状态位
            
            light_status.near_light ^= 1;
        }

        if (mouse_press(433,290,533,360) == 1) {
            // 等待左键释放
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
			last_blink1=clock();//重置计时器
		}
		if (mouse_press(100,290,200,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            light_status.left^=1;
			light_status.left_blink_state=light_status.left;
			last_blink=clock();//重置计时器
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
			last_blink1=clock();//重置计时器
			light_status.left^=1;
			light_status.left_blink_state=light_status.left;
			last_blink=clock();//重置计时器
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

/*另外，如果后面还做了时间，可以加入自动大灯
*/

void draw_light_page()
{
    bar1(0,0,633,630,0x000000);
	draw_botton(100,190,200,260,0x00FF,0x0000);
	draw_botton(100,290,200,360,0x00FF,0x0000);
	draw_botton(266,440,366,510,0x00FF,0x0000);
	draw_botton(433,190,533,260,0x00FF,0x0000);
	draw_botton(433,290,533,360,0x00FF,0x0000);
	//双闪  哎我没看见BMP.H里画三角形的函数，先就这样用几个直线凑合一下
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


