#include"allfunc.h"
#define PI 3.1415926537

void mainpage(CarStatus *state,int *puge)
{
	static int is_init_n=0,init_phase_n=0,is_init_s=0,init_phase_s=0;
	mouse_off(&mouse);

	draw_mainpage(state);



	mouse_on(mouse);


	while (1)
	{
		show_all(state);
		mouse_show(&mouse);
		if(!is_init_s)
		{
			switch(init_phase_s)
			{
                case 0: // 正向转动
                    if(needle_s(state,160))
					{
                        init_phase_s=1;
                        state->timer.drive_time_s=clock();
                    }
                    break;
                case 1: // 逆向转动
                    if(needle_s(state,20))
					{
                        is_init_s=1;
                    }
                    break;
			}
		}
		if(!is_init_n)
		{
			switch(init_phase_n)
			{
                case 0: // 正向转动
                    if(needle_n(state,160))
					{
                        init_phase_n=1;
                        state->timer.drive_time_n=clock();
                    }
                    break;
                case 1: // 逆向转动
                    if(needle_n(state,20))
					{
						is_init_n=1;
                    }
                    break;
			}
		}
		if (mouse_press(10,450,90,490) == 1)
		{
			*puge = 3;
			break;
		}
		if (mouse_press(10,500,90,540) == 1)
		{
			*puge = 4;
			break;
		}
		if (mouse_press(280,420,360,460) == 1)
		{
			*puge = 5;
			break;
		}
		if (mouse_press(10,550,90,590) == 1)
		{
			*puge = 6;
			break;
		}
		if (mouse_press(543,450,623,490) == 1)
		{
			*puge = 7;
			break;
		}
		if (mouse_press(543,500,623,540) == 1)
		{
			*puge = 8;//9,10,11,12 are used
			break;
		}
	}

}

//然后从main函数开始做的
void draw_mainpage(CarStatus *state)
{
	int i,x,y,x1,y1,x2,y2;
	bar1(0, 0, 1024, 768,0x0085);//和背景图中一样的深蓝色
	//Readbmp64k(0,0,"bmp\\background.bmp");
	Line_Thick(633, 0, 633, 768, 1, 0x7FFF);//和背景图中一样的亮浅绿色
	Line_Thick(0, 630, 633, 630, 1, 0x7FFF);
	Circle(829, 194, 180, 0x7FFF);
	Circle(829, 194, 179, 0x7FFF);
	Circle(829, 194, 178, 0x7FFF);
	Circle(829, 194, 177, 0x7FFF);
	Circle(829, 194, 176, 0x7FFF);
	bar1(640, 195, 1024, 768, 0x0085);
	Line_Thick(649, 194, 1009, 194, 1, 0x7FFF);
	Circle(829, 400, 180, 0x7FFF);
	Circle(829, 400, 179, 0x7FFF);
	Circle(829, 400, 178, 0x7FFF);
	Circle(829, 400, 177, 0x7FFF);
	Circle(829, 400, 176, 0x7FFF);
	bar1(640, 400, 1024,768, 0x0085);
	Line_Thick(649, 400, 1009, 400, 1, 0x7FFF);
	bar1(660, 450, 1000, 748, 0x000000);
	Readbmp64k(0,0,"bmp\\222.bmp");
	/*draw_botton(80, 70, 220, 200,MAGENTA,MAGENTA);
	draw_botton(80, 250, 220, 380, 0x00FF, 0xDDDD);
	draw_botton(80, 440, 220, 570, 0x00FF, 0xDDDD);
	draw_botton(380, 70, 520, 200, 0x00FF, 0xDDDD);
	draw_botton(380, 250, 520, 380, 0x00FF, 0xDDDD);
	draw_botton(380, 440, 520, 570, 0x00FF, 0xDDDD);
	puthz(110,119,"灯光",32,40,0xFFFFFF);
	puthz(410,119,"空调",32,40,0xFFFFFF);*/
	bar2(10,450,90,490,0xFFFFFF);
	bar2(10,500,90,540,0xFFFFFF);
	bar2(10,550,90,590,0xFFFFFF);//左边栏三个按钮
	puthz(25,458,"灯光",24,26,0XFFFFFF);
	puthz(25,508,"空调",24,26,0XFFFFFF);
	puthz(25,558,"雨刷",24,26,0XFFFFFF);
	bar2(543,450,623,490,0xFFFFFF);
	bar2(543,500,623,540,0xFFFFFF);
	bar2(543,550,623,590,0xFFFFFF);//右边栏三个按钮
	puthz(558,458,"驾驶",24,26,0XFFFFFF);
	puthz(558,508,"媒体",24,26,0XFFFFFF);
	puthz(558,558,"座椅",24,26,0XFFFFFF);
	bar2(280,420,360,460,0xFFFFFF);//中间的空调按钮
	puthz(295,428,"导航",24,26,0XFFFFFF);
	//下方状态栏
	puthz(5,635,"车内温度",32,33,0x7FFF);
	puthz(5,703,"预设温度",32,33,0x7FFF);
	bar2(140,703,172,735,0xFFFFFF);
	bar2(180,703,212,735,0xFFFFFF);
	Put_Asc16_Size(145,703,2,2,'+',0xFFFFFF);
	Put_Asc16_Size(185,703,2,2,'-',0xFFFFFF);
	prt_hz24_asc32(143,643, "0到35℃可调", 0xFFFFFF, "HZK\\Hzk24f");
	puthz(317,635,"车外天气",32,33,0x7FFF);
	switch(state->wiper_s.rain)
	{
		case 0:
			puthz(350,670,"晴天",32,33,0xFFFFFF);
			break;
		case 1:
			puthz(350,670,"小雨",32,33,0xFFFFFF);
			break;
		case 2:
			puthz(350,670,"大雨",32,33,0xFFFFFF);
			break;
	}
	puthz(829-16,195,"转速",16,17,0xFFFFFF);
	puthz(829-16,401,"速度",16,17,0xFFFFFF);
	for(i=20;i<170;i+=10)
	{
		x=(int)(829-176*cos(i*PI/180));
        y=(int)(400-176*sin(i*PI/180));
        x1=(int)(829-170*cos(i*PI/180));
        y1=(int)(400-170*sin(i*PI/180));
		x2=(int)(829-165*cos(i*PI/180));
        y2=(int)(400-165*sin(i*PI/180));
		Line2(x1,y1,x,y,0xFFFFFF);
		if(((i-20)/10)%2==0)
			put_asc16_number_size(x2,y2,1,1,(i-20)*2,0xFFFFFF);
	}
	for(i=20;i<170;i+=20)
	{
		x=(int)(829-176*cos(i*PI/180));
        y=(int)(194-176*sin(i*PI/180));
        x1=(int)(829-170*cos(i*PI/180));
        y1=(int)(194-170*sin(i*PI/180));
		x2=(int)(829-165*cos(i*PI/180));
        y2=(int)(194-165*sin(i*PI/180));
		Line2(x1,y1,x,y,0xFFFFFF);
		put_asc16_number_size(x2,y2,1,1,(i-20)/10,0xFFFFFF);
	}
}


void draw_botton(int x1, int y1, int x2, int y2, int Cowercolor, int Bordercolor)
{
	Cirbar(x1, y1, x2, y2, Bordercolor);
	Cirbar(x1, y1, x2, y2, Cowercolor);
}