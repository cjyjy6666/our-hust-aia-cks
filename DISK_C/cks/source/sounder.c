//这个sounder不是雷声是音响啊qaq只是sound是dos.h的关键字

#include"allfunc.h"

void sounder(CarStatus *state,int *puge)
{
	int volume=50;
	int sliderY=(int)(110+160*(100-volume)/100);
	const int sliderX=90;
	int newY;
	char vol_str[5];
	mouse_off(&mouse);
    sound_page();
	bar1(sliderX,sliderY,sliderX+20,sliderY+20,0xFFFFFF);
	sprintf(vol_str,"%d%",volume);
	put_asc16_size(80,350,2,2,vol_str,0xFFFFFF);
    mouse_on(mouse);

    while(1)
    {
        show_all(state);
		mouse_show(&mouse);
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 8;
			break;
		}
		if(mouse_press(80,100,120,300) == 1)
		{
			newY = mouse.y - 10;
			if(newY<110)
				newY=110;
			if(newY>270)
				newY=270;
			if(newY!=sliderY)
			{
				mouse_off(&mouse);
				bar1(sliderX,sliderY,sliderX+20,sliderY+20,0x0085);
				sliderY = newY;
				bar1(sliderX,sliderY,sliderX+20,sliderY+20,0xFFFFFF);
				mouse_on(mouse);
				volume = (int)(100 - 100*(sliderY-110)/160);
				bar1(80,350,160,382,0x0085);
				sprintf(vol_str,"%d%",volume);
				put_asc16_size(80,350,2,2,vol_str,0xFFFFFF);
			}
		}
    }
}

void sound_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
	//音量滑轨
	bar2(80,100,120,300,0xFFFFFF);
	bar1(81,101,119,299,0x0085);
	Put_Asc16_Size(90,60,2,2,'+',0xFFFFFF);
	Put_Asc16_Size(90,308,2,2,'-',0xFFFFFF);
	puthz(30,140,"音",32,32,0xFFFFFF);
	puthz(30,210,"量",32,32,0xFFFFFF);
	bar1(80,350,160,382,0x0085);//音量数值显示框
}