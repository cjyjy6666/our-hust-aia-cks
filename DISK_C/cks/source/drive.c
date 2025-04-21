#include"allfunc.h"
#define PI 3.1415926537

// 驾驶模式主函数 | Main function for drive mode control
void drive(CarStatus *state, int *puge)
{
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_drive_page(); // 绘制驾驶页面 | Draw drive page
    mouse_on(mouse);   // 开启鼠标显示 | Show mouse cursor
    
    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(100,90,200,160,"前进",&state->button_s.qianjin); 
        button2(100,190,200,260,"后退",&state->button_s.houtui); 
        button2(100,290,200,360,"泊车",&state->button_s.poche);
        button2(433,90,533,160,"运动",&state->button_s.yundong); 
        button2(433,190,533,260,"舒适",&state->button_s.shushi); 
        button2(433,290,533,360,"观光",&state->button_s.guanguang); 
        
        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 2;
            break;
        }
        
        // 前进模式按钮 | Forward mode button
        if(mouse_press(100,90,200,160) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            
            state->drive_s.forward = 1; // 设置前进模式 | Set forward mode
            state->drive_s.back = 0;
            state->drive_s.park = 0;
            state->drive_s.view = 0;
            state->drive_s.sport = 0;
            state->drive_s.comfort = 0;
            bar1(800,460,840,500,0x0000); // 清除仪表盘 | Clear dashboard
            state->drive_s.once_f = 0; // 重置状态 | Reset state
        }
        
        // 后退模式按钮 | Backward mode button
        if(mouse_press(100,190,200,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->drive_s.forward = 0;
            state->drive_s.back = 1; // 设置后退模式 | Set backward mode
            state->drive_s.park = 0;
            bar1(800,460,840,500,0x0000);
            state->drive_s.once_b = 0;
        }
        
        // 泊车模式按钮 | Parking mode button
        if(mouse_press(100,290,200,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->drive_s.forward = 0;
            state->drive_s.back = 0;
            state->drive_s.park = 1; // 设置泊车模式 | Set parking mode
            bar1(800,460,840,500,0x0000);
            state->drive_s.once_p = 0;
        }
        
        // 前进模式下的子模式 | Sub-modes under forward mode
        if(state->drive_s.forward) {
            // 运动模式按钮 | Sport mode button
            if(mouse_press(433,90,533,160) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                
                state->drive_s.sport = 1; // 设置运动模式 | Set sport mode
                state->drive_s.comfort = 0;
                state->drive_s.view = 0;
                bar1(800,460,840,500,0x0000);
                state->drive_s.once_s = 0;
            }
            
            // 舒适模式按钮 | Comfort mode button
            if(mouse_press(433,190,533,260) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                
                state->drive_s.comfort = 1; // 设置舒适模式 | Set comfort mode
                state->drive_s.sport = 0;
                state->drive_s.view = 0;
                bar1(800,460,840,500,0x0000);
            }
            
            // 观光模式按钮 | View mode button
            if(mouse_press(433,290,533,360) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                
                state->drive_s.view = 1; // 设置观光模式 | Set view mode
                state->drive_s.sport = 0;
                state->drive_s.comfort = 0;
                bar1(800,460,840,500,0x0000);
            }
        }
        else {
            // 非前进模式下重置子模式 | Reset sub-modes when not in forward mode
            state->drive_s.view = 0;
            state->drive_s.sport = 0;
            state->drive_s.comfort = 0;
        }
    }
}

// 绘制驾驶页面 | Draw drive page
void draw_drive_page()
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);
    
    // 绘制主模式按钮 | Draw main mode buttons
    bar1(100,90,200,160,0xC618); // 前进 | Forward
    bar1(100,190,200,260,0xC618); // 后退 | Backward
    bar1(100,290,200,360,0xC618); // 泊车 | Parking
    
    // 绘制子模式按钮 | Draw sub-mode buttons
    bar1(433,90,533,160,0xC618); // 运动 | Sport
    bar1(433,190,533,260,0xC618); // 舒适 | Comfort
    bar1(433,290,533,360,0xC618); // 观光 | View
    
    // 添加按钮文字 | Add button labels
    puthz(130, 115, "前进",24,30,0x000000); // 前进 | Forward
    puthz(130, 215, "后退",24,30,0x000000); // 后退 | Backward
    puthz(130, 315, "泊车",24,30,0x000000); // 泊车 | Parking
    puthz(463, 115, "运动",24,30,0x000000); // 运动 | Sport
    puthz(463, 215, "舒适",24,30,0x000000); // 舒适 | Comfort
    puthz(463, 315, "观光",24,30,0x000000); // 观光 | View
}

// 速度表指针控制 | Speedometer needle control
int needle_s(CarStatus *state, double s) // from 20~160
{
    int x, y, x1, y1;
    
    // 指针增加 | Needle increase
    if(state->drive_s.angle_s < s) {
        x = (int)(829-130*cos(state->drive_s.angle_s*PI/180));
        y = (int)(400-130*sin(state->drive_s.angle_s*PI/180));
        x1 = (int)(829-50*cos(state->drive_s.angle_s*PI/180));
        y1 = (int)(400-50*sin(state->drive_s.angle_s*PI/180));
        
        if((check_timer_expire(&(state->timer.drive_time_s), CLOCKS_PER_SEC/40)) && 
           (fabs(state->drive_s.angle_s-s) > 3)) {
            Line_Thick(x1,y1,x,y,14,0x0085); // 绘制指针 | Draw needle
            state->drive_s.angle_s += 3; // 增加角度 | Increase angle
        }
        
        if(fabs(state->drive_s.angle_s-s) < 5) {
            state->drive_s.angle_s = s; // 设置最终角度 | Set final angle
            return 1;
        }
        return 0;
    }
    
    // 指针减少 | Needle decrease
    if(state->drive_s.angle_s > s) {
        x = (int)(829-130*cos(state->drive_s.angle_s*PI/180));
        y = (int)(400-130*sin(state->drive_s.angle_s*PI/180));
        x1 = (int)(829-50*cos(state->drive_s.angle_s*PI/180));
        y1 = (int)(400-50*sin(state->drive_s.angle_s*PI/180));
        
        if((check_timer_expire(&(state->timer.drive_time_s), CLOCKS_PER_SEC/40)) && 
           (fabs(state->drive_s.angle_s-s) > 3)) {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_s -= 3; // 减少角度 | Decrease angle
        }
        
        if(fabs(state->drive_s.angle_s-s) < 5) {
            state->drive_s.angle_s = s;
            return 1;
        }
        return 0;
    }
}

// 转速表指针控制 | Tachometer needle control
int needle_n(CarStatus *state, double s) // from 20~160
{
    int x, y, x1, y1;
    
    // 指针增加 | Needle increase
    if(state->drive_s.angle_n < s) {
        x = (int)(829-130*cos(state->drive_s.angle_n*PI/180));
        y = (int)(194-130*sin(state->drive_s.angle_n*PI/180));
        x1 = (int)(829-50*cos(state->drive_s.angle_n*PI/180));
        y1 = (int)(194-50*sin(state->drive_s.angle_n*PI/180));
        
        if((check_timer_expire(&(state->timer.drive_time_n), CLOCKS_PER_SEC/40)) && 
           (fabs(state->drive_s.angle_n-s) > 3)) {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_n += 3;
        }
        
        if(fabs(state->drive_s.angle_n-s) < 5) {
            state->drive_s.angle_n = s;
            return 1;
        }
        return 0;
    }
    
    // 指针减少 | Needle decrease
    if(state->drive_s.angle_n > s) {
        x = (int)(829-130*cos(state->drive_s.angle_n*PI/180));
        y = (int)(194-130*sin(state->drive_s.angle_n*PI/180));
        x1 = (int)(829-50*cos(state->drive_s.angle_n*PI/180));
        y1 = (int)(194-50*sin(state->drive_s.angle_n*PI/180));
        
        if((check_timer_expire(&(state->timer.drive_time_n), CLOCKS_PER_SEC/40)) && 
           (fabs(state->drive_s.angle_n-s) > 3)) {
            Line_Thick(x1,y1,x,y,14,0x0085);
            state->drive_s.angle_n -= 3;
        }
        
        if(fabs(state->drive_s.angle_n-s) < 5) {
            state->drive_s.angle_n = s;
            return 1;
        }
        return 0;
    }
}

// 转速表指针变化控制 | Tachometer needle change control
int n_change(CarStatus *state)
{
    static int phase = 0; // 相位状态 | Phase state
    
    switch(phase) {
        case 0: // 正向转动 | Forward rotation
            if(needle_n(state,60)) {
                phase = 1;
                state->timer.drive_time_n = clock(); // 重置计时器 | Reset timer
            }
            break;
            
        case 1: // 逆向转动 | Reverse rotation
            if(needle_n(state,20)) {
                phase = 0;
                return 1;
            }
            break;
    }
    return 0;
}