#include"allfunc.h"
#define PI 3.1415926537

// 主页面控制函数 | Main page control function
void mainpage(CarStatus *state, int *puge)
{
    // 初始化状态变量 | Initialize state variables
    static int is_init_n = 0, init_phase_n = 0; // 转速表初始化状态 | Tachometer init state
    static int is_init_s = 0, init_phase_s = 0; // 速度表初始化状态 | Speedometer init state
    
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_mainpage(state); // 绘制主页面 | Draw main page
    mouse_on(mouse);   // 开启鼠标显示 | Show mouse cursor


    while (1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button1(10,450,90,490,"灯光",&state->button_s.dengguang); // 灯光按钮 | Light button
        button1(10,500,90,540,"空调",&state->button_s.kongtiao); // 空调按钮 | AC button
        button1(280,420,360,460,"导航",&state->button_s.daohang); // 导航按钮 | Navigation button
        button1(10,550,90,590,"雨刷",&state->button_s.yushua); // 雨刷按钮 | Wiper button
        button1(543,450,623,490,"驾驶",&state->button_s.jiashi); // 驾驶按钮 | Drive button
        button1(543,500,623,540,"媒体",&state->button_s.meiti); // 媒体按钮 | Media button
        button1(543,550,623,590,"座椅",&state->button_s.zuoyi); // 座椅按钮 | Left button
        button1(0,0,80,40,"注销",&state->button_s.zhuxiao); // 退出按钮 | Exit button


        
        // 速度表初始化动画 | Speedometer initialization animation
        if(!is_init_s) {
            switch(init_phase_s) {
                case 0: // 正向转动 | Forward rotation
                    if(needle_s(state,160)) {
                        init_phase_s = 1;
                        state->timer.drive_time_s = clock();
                    }
                    break;
                case 1: // 逆向转动 | Reverse rotation
                    if(needle_s(state,20)) {
                        is_init_s = 1;
                    }
                    break;
            }
        }
        
        // 转速表初始化动画 | Tachometer initialization animation
        if(!is_init_n) {
            switch(init_phase_n) {
                case 0: // 正向转动 | Forward rotation
                    if(needle_n(state,160)) {
                        init_phase_n = 1;
                        state->timer.drive_time_n = clock();
                    }
                    break;
                case 1: // 逆向转动 | Reverse rotation
                    if(needle_n(state,20)) {
                        is_init_n = 1;
                    }
                    break;
            }
        }
        
        // 灯光按钮 | Light button
        if (mouse_press(10,450,90,490) == 1) {
            *puge = 3; // 跳转至灯光页面 | Jump to light page
            break;
        }
        
        // 空调按钮 | AC button
        if (mouse_press(10,500,90,540) == 1) {
            *puge = 4; // 跳转至空调页面 | Jump to AC page
            break;
        }
        
        // 导航按钮 | Navigation button
        if (mouse_press(280,420,360,460) == 1) {
            *puge = 5; // 跳转至导航页面 | Jump to navigation page
            break;
        }
        
        // 雨刷按钮 | Wiper button
        if (mouse_press(10,550,90,590) == 1) {
            *puge = 6; // 跳转至雨刷页面 | Jump to wiper page
            break;
        }
        
        // 驾驶按钮 | Drive button
        if (mouse_press(543,450,623,490) == 1) {
            *puge = 7; // 跳转至驾驶页面 | Jump to drive page
            break;
        }
        
        // 媒体按钮 | Media button
        if (mouse_press(543,500,623,540) == 1) {
            *puge = 8; // 跳转至媒体页面 | Jump to media page
            break;
        }

        // 座椅按钮 | Left button
        if (mouse_press(543,550,623,590) == 1) {
            *puge = 13; // 跳转至座椅页面 | Jump to left page
            break;
        }

        if(mouse_press(0,0,80,40)==1){ 
            exit(1);// 退出按钮 | Exit button

        }
    }
}

// 绘制主页面 | Draw main page
void draw_mainpage(CarStatus *state)
{
    int i, x, y, x1, y1, x2, y2;
    
    // 绘制背景 | Draw background
    bar1(0, 0, 1024, 768, 0x0085); // 深蓝色背景 | Dark blue background
    Line_Thick(633, 0, 633, 768, 1, 0x7FFF); // 垂直分割线 | Vertical divider
    Line_Thick(0, 630, 633, 630, 1, 0x7FFF); // 水平分割线 | Horizontal divider
    
    // 绘制转速表 | Draw tachometer
    for(i = 0; i < 5; i++) {
        Circle(829, 194, 180-i, 0x7FFF); // 转速表外圈 | Tachometer outer circle
    }
    bar1(640, 195, 1024, 768, 0x0085); // 转速表背景 | Tachometer background
    Line_Thick(649, 194, 1009, 194, 1, 0x7FFF); // 转速表水平线 | Tachometer horizontal line
    
    // 绘制速度表 | Draw speedometer
    for(i = 0; i < 5; i++) {
        Circle(829, 400, 180-i, 0x7FFF); // 速度表外圈 | Speedometer outer circle
    }
    bar1(640, 400, 1024, 768, 0x0085); // 速度表背景 | Speedometer background
    Line_Thick(649, 400, 1009, 400, 1, 0x7FFF); // 速度表水平线 | Speedometer horizontal line
    
    // 绘制中央区域 | Draw center area
    bar1(660, 450, 1000, 748, 0x000000); // 黑色背景 | Black background
    Readbmp64k(0,0,"bmp\\222.bmp"); // 读取背景图片 | Load background image
    
    // 绘制左侧按钮 | Draw left buttons
    bar1(10,450,90,490,0xC618); // 灯光按钮 | Light button
    bar1(10,500,90,540,0xC618); // 空调按钮 | AC button
    bar1(10,550,90,590,0xC618); // 雨刷按钮 | Wiper button
    puthz(25,458,"灯光",24,26,0X000000); // 灯光文字 | Light text
    puthz(25,508,"空调",24,26,0X000000); // 空调文字 | AC text
    puthz(25,558,"雨刷",24,26,0X000000); // 雨刷文字 | Wiper text
    
    // 绘制右侧按钮 | Draw right buttons
    bar1(543,450,623,490,0xC618); // 驾驶按钮 | Drive button
    bar1(543,500,623,540,0xC618); // 媒体按钮 | Media button
    bar1(543,550,623,590,0xC618); // 座椅按钮 | Seat button
    puthz(558,458,"驾驶",24,26,0X000000); // 驾驶文字 | Drive text
    puthz(558,508,"媒体",24,26,0X000000); // 媒体文字 | Media text
    puthz(558,558,"座椅",24,26,0X000000); // 座椅文字 | Seat text
    
    // 绘制中央导航按钮 | Draw center navigation button
    bar1(280,420,360,460,0xC618); 
    puthz(295,428,"导航",24,26,0X000000); // 导航文字 | Navigation text
    
    // 绘制状态栏 | Draw status bar
    puthz(5,635,"车内温度",32,33,0x7FFF); // 车内温度 | Interior temperature
    puthz(5,703,"预设温度",32,33,0x7FFF); // 预设温度 | Preset temperature
    bar2(140,703,172,735,0xFFFFFF); // 温度+按钮 | Temp + button
    bar2(180,703,212,735,0xFFFFFF); // 温度-按钮 | Temp - button
    Put_Asc16_Size(145,703,2,2,'+',0xFFFFFF); // +符号 | + symbol
    Put_Asc16_Size(185,703,2,2,'-',0xFFFFFF); // -符号 | - symbol
    prt_hz24_asc32(143,643, "0到35℃可调", 0xFFFFFF, "HZK\\Hzk24f"); // 温度范围 | Temp range
    
    bar1(0,0,80,40,0xC618);
    puthz(15,8,"注销",24,26,0X000000); // 注销按钮 | Logout button
    prt_hz24_asc32(800,530, "安全带情况:正常", 0x7FFF, "HZK\\Hzk24f");
    prt_hz24_asc32(800,570, "剩余油量:50L", 0x7FFF, "HZK\\Hzk24f");

    // 显示天气状态 | Display weather status
    puthz(317,635,"车外天气",32,33,0x7FFF); // 车外天气 | Exterior weather
    switch(state->wiper_s.rain) {
        case 0: puthz(350,670,"晴天",32,33,0xFFFFFF); break; // 晴天 | Sunny
        case 1: puthz(350,670,"小雨",32,33,0xFFFFFF); break; // 小雨 | Light rain
        case 2: puthz(350,670,"大雨",32,33,0xFFFFFF); break; // 大雨 | Heavy rain
    }
    
    // 添加仪表标签 | Add gauge labels
    puthz(829-16,195,"转速",16,17,0xFFFFFF); // 转速 | RPM
    puthz(829-16,401,"速度",16,17,0xFFFFFF); // 速度 | Speed
    
    // 绘制速度表刻度 | Draw speedometer scale
    for(i = 20; i < 170; i += 10) {
        x = (int)(829-176*cos(i*PI/180));
        y = (int)(400-176*sin(i*PI/180));
        x1 = (int)(829-170*cos(i*PI/180));
        y1 = (int)(400-170*sin(i*PI/180));
        x2 = (int)(829-165*cos(i*PI/180));
        y2 = (int)(400-165*sin(i*PI/180));
        Line2(x1,y1,x,y,0xFFFFFF); // 刻度线 | Scale line
        if(((i-20)/10)%2 == 0)
            put_asc16_number_size(x2,y2,1,1,(i-20)*2,0xFFFFFF); // 刻度值 | Scale value
    }
    
    // 绘制转速表刻度 | Draw tachometer scale
    for(i = 20; i < 170; i += 20) {
        x = (int)(829-176*cos(i*PI/180));
        y = (int)(194-176*sin(i*PI/180));
        x1 = (int)(829-170*cos(i*PI/180));
        y1 = (int)(194-170*sin(i*PI/180));
        x2 = (int)(829-165*cos(i*PI/180));
        y2 = (int)(194-165*sin(i*PI/180));
        Line2(x1,y1,x,y,0xFFFFFF); // 刻度线 | Scale line
        put_asc16_number_size(x2,y2,1,1,(i-20)/10,0xFFFFFF); // 刻度值 | Scale value
    }

    //空调状态显示 | AC status display
    puthz(455,635,"空调状态",32,33,0x7FFF);
    puthz(521,668,"关闭",32,33,0xFFFFFF);
}

// 绘制按钮函数 | Draw button function
void draw_botton(int x1, int y1, int x2, int y2, int Cowercolor, int Bordercolor)
{
    Cirbar(x1, y1, x2, y2, Bordercolor); // 绘制按钮边框 | Draw button border
    Cirbar(x1, y1, x2, y2, Cowercolor);  // 绘制按钮主体 | Draw button body
}