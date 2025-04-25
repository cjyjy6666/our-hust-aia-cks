#include"allfunc.h"

// 车灯控制主函数 | Main function for light control
void light(CarStatus* state, int *puge)
{
    uint8_t new_state; // 新状态变量 | New state variable
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_light_page(); // 绘制车灯页面 | Draw light page
    mouse_on(mouse);   // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(100,290,200,360,"左转",&state->button_s.zuozhuan); // 左转向灯按钮 | Left turn signal button
        button2(100,190,200,260,"右转",&state->button_s.youzhuan); // 右转向灯按钮 | Right turn signal button
        button2(266,290,366,360,"雾灯",&state->button_s.wudeng); // 雾灯按钮 | Fog light button
        button2(433,190,533,260,"近光",&state->button_s.jinguang); // 近光灯按钮 | Near light button
        button2(433,290,533,360,"远光",&state->button_s.yuanguang); // 远光灯按钮 | Far light button
        button5(603,600,633,630,&state->button_s.xxx); // 返回按钮 | Back button


        // 近光灯按钮 | Near light button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse); 
                mouse_show(&mouse); 
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            
            state->light_s.near_light ^= 1; // 切换近光灯状态 | Toggle near light state
        }

        // 远光灯按钮 | Far light button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->light_s.far_light ^= 1; // 切换远光灯状态 | Toggle far light state
        }

        // 右转向灯按钮 | Right turn signal button
        if (mouse_press(100,190,200,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 如果左转向灯开启则关闭 | If left turn is on, turn it off
            if(state->light_s.left) {
                state->light_s.left = 0;
                state->light_s.left_blink_state = 0;
            }

            state->light_s.right ^= 1; // 切换右转向灯状态 | Toggle right turn signal
            state->light_s.right_blink_state = state->light_s.right; // 同步闪烁状态 | Sync blink state
        }

        // 左转向灯按钮 | Left turn signal button
        if (mouse_press(100,290,200,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 如果右转向灯开启则关闭 | If right turn is on, turn it off
            if(state->light_s.right) {
                state->light_s.right = 0;
                state->light_s.right_blink_state = 0;
            }
            
            state->light_s.left ^= 1; // 切换左转向灯状态 | Toggle left turn signal
            state->light_s.left_blink_state = state->light_s.left; // 同步闪烁状态 | Sync blink state
        }

        // 雾灯按钮 | Fog light button
        if (mouse_press(266,290,366,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->light_s.fog ^= 1; // 切换雾灯状态 | Toggle fog light state
        }

        // 危险警告灯按钮 | Hazard warning light button
        if (mouse_press(266,63,366,150) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 切换危险警告灯状态 | Toggle hazard warning lights
            new_state = !(state->light_s.right && state->light_s.left);
            state->light_s.right = new_state;
            state->light_s.left = new_state;
            state->light_s.right_blink_state = new_state;
            state->light_s.left_blink_state = new_state;
        }

        // 返回按钮 | Back button
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 2; // 返回主页面 | Return to main page
            break;
        }
    }
}

// 绘制车灯控制页面 | Draw light control page
void draw_light_page()
{
    // 绘制按钮 | Draw buttons
    bar1(100,190,200,260,0xC618); // 右转向灯 | Right turn signal
    bar1(100,290,200,360,0xC618); // 左转向灯 | Left turn signal
    bar1(266,290,366,360,0xC618); // 雾灯 | Fog light
    bar1(433,190,533,260,0xC618); // 近光灯 | Near light
    bar1(433,290,533,360,0xC618); // 远光灯 | Far light
    
    // 绘制危险警告灯三角形 | Draw hazard warning triangle
    Line2(316,63,266,150,0xF800);
    Line2(316,63,366,150,0xF800);
    Line2(266,150,366,150,0xF800);
    Line2(316,73,275,145,0xF800);
    Line2(316,73,357,145,0xF800);
    Line2(275,145,357,145,0xF800);
    Put_Asc16_Size(308, 100, 2, 2, '!', 0xF800); // 感叹号 | Exclamation mark
    
    // 添加按钮文字 | Add button labels
    puthz(130, 215, "右转",24,30,0x000000); // 右转 | Right turn
    puthz(130, 315, "左转",24,30,0x000000); // 左转 | Left turn
    puthz(296, 315, "雾灯",24,30,0x000000); // 雾灯 | Fog light
    puthz(463, 215, "近光",24,30,0x000000); // 近光 | Near light
    puthz(463, 315, "远光",24,30,0x000000); // 远光 | Far light
    
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);
}


