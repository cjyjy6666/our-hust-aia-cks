#include"allfunc.h"



void light(int *puge)
{
	CarStatus *status = get_car_status();
	uint8_t new_state;
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while(1)
	{
		show_all();
		
		mouse_show(&mouse);
        
        // 修改鼠标检测逻辑：增加释放检测防抖
        if (mouse_press(433,190,533,260) == 1) {
            // 等待左键释放
            do {
                MouseGet(&mouse);      // 持续获取最新状态
                mouse_show(&mouse);   // 保持鼠标显示更新
            } while ((mouse.key & 1) == 1);  // 检查左键状态位
            
            status->light_status.near_light ^= 1;
        }

        if (mouse_press(433,290,533,360) == 1) {
            // 等待左键释放
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            status->light_status.far_light ^= 1;    
        }

		if (mouse_press(100,190,200,260) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
			if(status->light_status.left) {
                status->light_status.left = 0;
                status->light_status.left_blink_state = 0;
    
            }

            status->light_status.right^=1;
			status->light_status.right_blink_state=status->light_status.right;
			
		}
		if (mouse_press(100,290,200,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
			if(status->light_status.right) {
                status->light_status.right = 0;
                status->light_status.right_blink_state = 0;
                
            }
			
            status->light_status.left^=1;
			status->light_status.left_blink_state=status->light_status.left;
			
		}
		if (mouse_press(266,440,366,510) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            status->light_status.fog ^= 1;
		}
		if (mouse_press(266,63,366,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 切换双闪状态
            new_state = !(status->light_status.right && status->light_status.left);
            status->light_status.right = new_state;
            status->light_status.left = new_state;
            status->light_status.right_blink_state = new_state;
            status->light_status.left_blink_state = new_state;
            
            
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
    bar1(0,0,633,630,0xFFFFFF);
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
	Line2(603,600,633,600,0x000000);
	Line2(603,600,603,630,0x000000);
	Line2(603,600,633,630,0x000000);
	Line2(633,600,603,630,0x000000);
}


