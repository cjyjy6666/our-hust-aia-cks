#include"allfunc.h"

// 空调控制主函数 | Main function for AC control
void ac(CarStatus *state,int *puge)
{
	mouse_off(&mouse);    // 关闭鼠标显示 | Hide mouse cursor
    draw_ac_page();       // 绘制空调页面 | Draw AC control page
    mouse_on(mouse);      // 开启鼠标显示 | Show mouse cursor

    while(1)             // 主控制循环 | Main control loop
    {
        show_all(state); // 显示所有状态 | Display all status
		temp(state);     // 温度控制处理 | Temperature control handling
		mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(100,90,200,160,"自动",&state->button_s.zidong); // 自动模式按钮 | Auto mode button
        button2(100,190,200,260,"制冷",&state->button_s.zhilen); // 制冷模式按钮 | Cooling mode button
        button2(100,290,200,360,"暖风",&state->button_s.nuanfeng); // 暖风模式按钮 | Heating mode button
        button2(433,90,533,160,"循环",&state->button_s.xunhuan); // 循环模式按钮 | Circulation mode button
        button2(433,190,533,260,"通风",&state->button_s.tongfeng); // 新风模式按钮 | Fresh air mode button
        button2(433,290,533,360,"除雾",&state->button_s.chuwu); // 定温模式按钮 | Fixed temperature mode button
        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;   // 返回主页面 | Return to main page
			break;
		}
        
        // 自动模式按钮 | Auto mode button
        if(mouse_press(100,90,200,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            if(state->ac_s.ac_state == 1)
                state->ac_s.ac_state = 0; // 关闭自动模式 | Turn off auto mode
            else
            {
                state->ac_s.ac_state = 1; // 开启自动模式 | Turn on auto mode
            }
        }
        
        // 制冷模式按钮 | Cooling mode button
        if(mouse_press(100,190,200,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 2)
                state->ac_s.ac_state = 0; // 关闭制冷模式 | Turn off cooling mode
            else
            {
                state->ac_s.ac_state = 2; // 开启制冷模式 | Turn on cooling mode
                state->ac_s.target_temp = state->ac_s.current_temp-1; // 设置目标温度 | Set target temp
            }
        }
        
        // 暖风模式按钮 | Heating mode button
        if(mouse_press(100,290,200,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 3)
                state->ac_s.ac_state = 0; // 关闭暖风模式 | Turn off heating mode
            else
            {
                state->ac_s.ac_state = 3; // 开启暖风模式 | Turn on heating mode
                state->ac_s.target_temp = state->ac_s.current_temp+1; // 设置目标温度 | Set target temp
            }
        }
        
        // 循环模式按钮 | Circulation mode button
        if(mouse_press(433,90,533,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.circulate ^= 1; // 切换循环模式 | Toggle circulation mode
        }
        
        // 通风模式按钮 | Fresh air mode button
        if(mouse_press(433,190,533,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.fresh_air ^= 1; // 切换通风模式 | Toggle fresh air mode
        }
        
        // 除雾模式按钮 | Defog mode button
        if(mouse_press(433,290,533,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.defog ^= 1; // 切换除雾模式 | Toggle defog mode
        }
    }
}

// 绘制空调控制页面 | Draw AC control page
void draw_ac_page()
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
    
    // 绘制模式选择按钮 | Draw mode selection buttons
    bar1(100,90,200,160,0xC618);  // 自动模式 | Auto mode
	bar1(100,190,200,260,0xC618); // 制冷模式 | Cooling mode
    bar1(100,290,200,360,0xC618); // 暖风模式 | Heating mode
    bar1(433,90,533,160,0xC618);  // 循环模式 | Circulation mode
	bar1(433,190,533,260,0xC618); // 通风模式 | Fresh air mode
    bar1(433,290,533,360,0xC618); // 除雾模式 | Defog mode

    // 添加按钮文字 | Add button labels
    puthz(130, 115, "自动",24,30,0x000000); // 自动 | Auto
    puthz(130, 215, "制冷",24,30,0x000000); // 制冷 | Cooling
    puthz(130, 315, "暖风",24,30,0x000000); // 暖风 | Heating
    puthz(463, 115, "循环",24,30,0x000000); // 循环 | Circulation
    puthz(463, 215, "通风",24,30,0x000000); // 通风 | Fresh air
    puthz(463, 315, "除雾",24,30,0x000000); // 除雾 | Defog
}

// 温度控制处理 | Temperature control handling
void temp(CarStatus *state)
{
    char tag_temp[5]={'\0'};
    FILE *fp;
    prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
    
    // 自动模式温度控制 | Auto mode temperature control
    if(state->ac_s.ac_state == 1)
    {
        if(state->ac_s.target_temp<=35&&state->ac_s.target_temp>=0)
        {
            // 温度增加按钮 | Temperature increase button
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.target_temp<35)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
                fp=fopen("data\\temp.dat","wb+");
                fwrite(&state->ac_s.target_temp,sizeof(int),1,fp);
                fclose(fp);
            }
            // 温度减少按钮 | Temperature decrease button
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.target_temp>0)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
                fp=fopen("data\\temp.dat","wb+");
                fwrite(&state->ac_s.target_temp,sizeof(int),1,fp);
                fclose(fp);
            } 
        }
    }
    
    // 制冷模式温度控制 | Cooling mode temperature control
    if(state->ac_s.ac_state == 2)
    {
        if(state->ac_s.target_temp>=0&&state->ac_s.current_temp>=state->ac_s.target_temp)
        {
            // 温度增加按钮 | Temperature increase button
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.cur_t>state->ac_s.target_temp)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
            // 温度减少按钮 | Temperature decrease button
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.target_temp>0)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
        } 
    }
    
    // 暖风模式温度控制 | Heating mode temperature control
    if(state->ac_s.ac_state == 3)
    {
        if(state->ac_s.target_temp<=35&&state->ac_s.current_temp<=state->ac_s.target_temp)
        {
            // 温度增加按钮 | Temperature increase button
            if(mouse_press(140,703,172,735) == 1&&state->ac_s.target_temp<35)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp++;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
            // 温度减少按钮 | Temperature decrease button
            if(mouse_press(180,703,212,735) == 1&&state->ac_s.cur_t<state->ac_s.target_temp)
            {
                do
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                }while ((mouse.key & 1) == 1);
                state->ac_s.target_temp--;
                bar1(40,735,130,770,0x0085);
                sprintf(tag_temp,"%d℃",state->ac_s.target_temp);
                prt_hz24_asc32(40,735,tag_temp,0xFC44,"HZK\\Hzk24f");
            }
        } 
    }
}

// 温度变化处理 | Temperature change handling
void temp_change(CarStatus *state)
{
    if(state->ac_s.ac_state) // 如果空调开启 | If AC is on
    {
        if(check_timer_expire(&(state->timer.ac_time),4*CLOCKS_PER_SEC)) 
        {
            // 当前温度低于目标温度 | Current temp lower than target
            if(state->ac_s.current_temp < state->ac_s.target_temp) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp++; // 温度升高 | Increase temperature
            } 
            // 当前温度高于目标温度 | Current temp higher than target
            else if(state->ac_s.current_temp > state->ac_s.target_temp) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp--; // 温度降低 | Decrease temperature
            }
        }
    }
    else // 如果空调关闭 | If AC is off
    {
        if(check_timer_expire(&(state->timer.ac_time),4*CLOCKS_PER_SEC)) 
        {
            // 当前温度低于环境温度 | Current temp lower than ambient
            if(state->ac_s.current_temp < state->ac_s.cur_t) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp++; // 温度升高 | Increase temperature
            } 
            // 当前温度高于环境温度 | Current temp higher than ambient
            else if(state->ac_s.current_temp > state->ac_s.cur_t) 
            {
                bar1(40,667,130,702,0x0085);
                state->ac_s.current_temp--; // 温度降低 | Decrease temperature
            }
        }
    }
}