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
            state->media_s.initialized=0;
            state->media_s.first_time=1;
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
		show_sound(state,volume);
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
	bar1(180,100,550,350,0x0085);//音效显示区
}

int clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

//move_bar 函数：用当前的 y 值指针更新动画位置
//当前位置 *py 趋近到目标 target 时返回 1（表示该段运动完成），否则返回 0
int move_bar(CarStatus *state, int *py, int target, int x,int i,int color)
{
    // *py 为当前矩形条的 y 坐标（持久化保存）
    if(*py > target)
    {
        if(check_timer_expire(&(state->timer.sounder_time[i]), CLOCKS_PER_SEC/200))
        {
			int delta = ( *py - target ) / 5;
            //bar1(x, *py - 1, x+40, *py, 0x7FFF);
			//bar1(x,110,x+40,340,0x0085);
			//bar1(x,*py-1,x+40,340,0x7FFF);
            // 计算步长，至少为1
            if(delta <= 0)
                delta = 1;
			bar1(x,*py-delta,x+40,*py,color);
            *py -= delta;
            if(*py <= target)
            {
                *py = target;
                return 1;
            }
        }
    }
    else if(*py < target)
    {
        if(check_timer_expire(&(state->timer.sounder_time[i]), CLOCKS_PER_SEC/200))
        {
			int delta = (target - *py) / 5;
            //bar1(x, *py, x+40, *py + 1, 0x0085);
			//bar1(x,110,x+40,340,0x0085);
			//bar1(x,*py+1,x+40,340,0x7FFF);
            if(delta <= 0)
                delta = 1;
			bar1(x,*py,x+40,*py+delta,0x0085);
            *py += delta;
            if(*py >= target)
            {
                *py = target;
                return 1;
            }
        }
    }
    else // already equal 
        return 1;
    return 0;
}

void show_sound(CarStatus *state, int volume)
{
    int color;
    // 静态数组保存每个条的状态和动画周期状态
    static int peak[9]={0};       // 波峰位置
    static int valley[9]={0};     // 波谷位置
    static int balance=0;         // 基础平衡位置（均同一个）
    static int b[9]={0};          // 平衡位置漂移量
    static int b_signal[9]={0};   // 漂移量符号
    static int balance_p[9]={0};  // 下一周期计算的目标平衡位置
    static int amplitude[9]={0};  // 振幅
    static int cycle[9]={0};      // 当前周期状态：0、1、2分别对应不同阶段
    static int current_y[9]={0};  // 每个矩形条当前的 y 坐标（动画状态持久化）

    int i;
    // 初始阶段：根据 volume 计算初始平衡位置及相关参数，并初始化当前 y 值
    if(!state->media_s.initialized)
    {
        balance = (int)(340 - 2.3 * volume);
        //bar1(185, balance, 545, 340, 0x7FFF);  // 初始绘制
        for(i = 0; i < 9; i++)
        {
            if(i%2==0)
                bar1(185 + i * 40, balance, 225+i*40, 340, 0x7FFF); // 初始绘制
            else
                bar1(185 + i * 40, balance, 225+i*40, 340, 0x0B5F); // 初始绘制
            b_signal[i] = random(2);
            b[i] = random((int)(0.1 * balance) + 1);
            if(b_signal[i])
                b[i] = -b[i];
            balance_p[i] = clamp(balance + b[i], 110, 340);
            amplitude[i] = random((int)(0.5*(340-balance_p[i])) + 1);
            peak[i] = clamp(balance_p[i] - amplitude[i],110,340);
            valley[i] = clamp(balance_p[i] + amplitude[i],110,340);
            // 用初始的平衡位置作为当前的起点
            current_y[i] = balance_p[i];
            cycle[i] = 0;
        }
        state->media_s.initialized = 1;
    }
    // 对每个矩形条依次进行动画阶段处理
    // 周期：
    // cycle 0: 从当前平衡位置(current_y)移动到波峰 peak
    // cycle 1: 从波峰移动到波谷 valley
    // cycle 2: 重新计算下一周期的平衡位置，并从波谷移动到该平衡位置
    for(i = 0; i < 9; i++)
    {
        if(i%2==0)
            color=0x7FFF;
        else
            color=0x0B5F;
        switch(cycle[i])
        {
            case 0:
                if(move_bar(state, &current_y[i], peak[i], 185 + i * 40,i,color))
                {
                    cycle[i] = 1;
                }
                break;
            case 1:
                if(move_bar(state, &current_y[i], valley[i], 185 + i * 40,i,color))
                {
                    cycle[i] = 2;
                }
                break;
            case 2:
            {
				if(!state->media_s.first_time)
				{
					// 计算新的漂移、平衡、振幅、波峰、波谷
					balance = (int)(340 - 2.3 * volume);
					b_signal[i] = random(2);
					b[i] = random((int)(0.1 * balance) + 1);
					if(b_signal[i])
						b[i] = -b[i];
					balance_p[i] = clamp(balance + b[i], 110, 340);
				}
                // 将当前状态强制从 valley 移动到新的平衡位置
                if(move_bar(state, &current_y[i], balance_p[i], 185 + i * 40,i,color))
                {
                    amplitude[i] = random((int)(0.5*(340-balance_p[i])) + 1);
                    peak[i] = clamp(balance_p[i]-amplitude[i],110,340);
                    valley[i] = clamp(balance_p[i] + amplitude[i],110,340);
                    cycle[i] = 0;
					state->media_s.first_time=0;
                }
                break;
            }
        }
    }
}