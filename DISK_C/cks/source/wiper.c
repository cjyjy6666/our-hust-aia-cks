#include"allfunc.h"

// 雨刷控制主函数 | Main function for wiper control
void wiper(CarStatus *state, int *puge)
{
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_wiper_page(); // 绘制雨刷页面 | Draw wiper page
    mouse_on(mouse);   // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(100,190,200,260,"自动",&state->button_s.zidong2); 
        button2(100,290,200,360,"手动",&state->button_s.shoudong); 
        button2(433,190,533,260,"高速",&state->button_s.kuaisu); 
        button2(433,290,533,360,"低速",&state->button_s.mansu); 
        button5(603,600,633,630,&state->button_s.xxx); // 返回按钮 | Back button

        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 2; // 返回主页面 | Return to main page
            break;
        }
        
        // 自动模式按钮 | Auto mode button
        if (mouse_press(100,190,200,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            state->wiper_s.auto_w ^= 1; // 切换自动模式 | Toggle auto mode
            state->wiper_s.once = 0;   // 关闭单次模式 | Disable once mode
            state->wiper_s.fast = 0;   // 关闭快速模式 | Disable fast mode
            state->wiper_s.slow = 0;   // 关闭慢速模式 | Disable slow mode
        }
        
        // 手动模式按钮 | Manual mode button
        if (mouse_press(100,290,200,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.once ^= 1; // 切换单次模式 | Toggle once mode
            state->wiper_s.fast = 0;
            state->wiper_s.slow = 0;
            state->wiper_s.auto_w = 0;
            state->timer.wiper_time = clock(); // 记录时间 | Record time
        }
        
        // 快速模式按钮 | Fast mode button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.fast ^= 1; // 切换快速模式 | Toggle fast mode
            state->wiper_s.slow = 0;
            state->wiper_s.auto_w = 0;
            state->wiper_s.once = 0;
        }
        
        // 慢速模式按钮 | Slow mode button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.slow ^= 1; // 切换慢速模式 | Toggle slow mode
            state->wiper_s.fast = 0;
            state->wiper_s.auto_w = 0;
            state->wiper_s.once = 0;
        }
        
        /* 雨刷逻辑 | Wiper logic */
        // 自动模式优先 | Auto mode has highest priority
        if(state->wiper_s.auto_w) {
            if(state->wiper_s.rain == 2) {       // 大雨 | Heavy rain
                state->wiper_s.cur_wip = 2;     // 快速雨刷 | Fast wiper
            } 
            else if(state->wiper_s.rain == 1) { // 小雨 | Light rain
                state->wiper_s.cur_wip = 1;     // 慢速雨刷 | Slow wiper
            } 
            else {                              // 晴天 | Sunny
                state->wiper_s.cur_wip = 0;     // 关闭雨刷 | Turn off wiper
            }
        }
        // 手动模式（互斥）| Manual mode (mutually exclusive)
        else if(state->wiper_s.fast) {
            state->wiper_s.cur_wip = 2; // 快速雨刷 | Fast wiper
        }
        else if(state->wiper_s.slow) {
            state->wiper_s.cur_wip = 1; // 慢速雨刷 | Slow wiper
        }
        // 单次模式（最高优先级）| Once mode (highest priority)
        else if(state->wiper_s.once) {
            state->wiper_s.cur_wip = 1;  // 改为慢速刮 | Change to slow wipe
            if(check_timer_expire(&(state->timer.wiper_time), CLOCKS_PER_SEC)) {
                state->wiper_s.cur_wip = 0; // 关闭雨刷 | Turn off wiper
                state->wiper_s.once = 0;   // 重置单次模式 | Reset once mode
            }
        }
        // 默认状态 | Default state
        else {
            state->wiper_s.cur_wip = 0; // 关闭雨刷 | Turn off wiper
        }
    }
}

// 绘制雨刷页面 | Draw wiper page
void draw_wiper_page()
{
    // 绘制功能按钮 | Draw function buttons
    bar1(100,190,200,260,0xC618); // 自动按钮 | Auto button
    bar1(100,290,200,360,0xC618); // 手动按钮 | Manual button
    bar1(433,190,533,260,0xC618); // 快速按钮 | Fast button
    bar1(433,290,533,360,0xC618); // 慢速按钮 | Slow button
    
    // 添加按钮文字 | Add button labels
    puthz(130, 215, "自动",24,30,0x000000); // 自动 | Auto
    puthz(130, 315, "手动",24,30,0x000000); // 手动 | Manual
    puthz(463, 215, "高速",24,30,0x000000); // 高速 | Fast
    puthz(463, 315, "低速",24,30,0x000000); // 低速 | Slow
    
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);
}