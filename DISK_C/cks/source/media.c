#include"allfunc.h"

// 媒体控制主函数 | Main function for media control
void media(CarStatus *state, int *puge)
{
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_media_page(); // 绘制媒体页面 | Draw media page
    mouse_on(mouse);   // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(100,190,200,260,"拨号",&state->button_s.bohao); // 拨号按钮 | Dial button
        button2(100,290,200,360,"通讯",&state->button_s.tongxun); // 通讯录按钮 | Contact button
        button2(433,190,533,260,"音乐",&state->button_s.yinyue); // 音乐按钮 | Music button
        button2(433,290,533,360,"音响",&state->button_s.yinxiang); // 音响按钮 | Sound button
        button5(603,600,633,630,&state->button_s.xxx); // 返回按钮 | Back button

        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 2; // 返回主页面 | Return to main page
            break;
        }
        
        // 拨号按钮 | Dial button
        if (mouse_press(100,190,200,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            *puge = 9; // 跳转至拨号页面 | Jump to dial page
            break;
        }
        
        // 通讯录按钮 | Contact button
        if (mouse_press(100,290,200,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge = 10; // 跳转至通讯录页面 | Jump to contact page
            break;
        }
        
        // 音乐按钮 | Music button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge = 11; // 跳转至音乐页面 | Jump to music page
            break;
        }
        
        // 音响按钮 | Sound button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            *puge = 12; // 跳转至音响控制页面 | Jump to sound control page
            break;
        }
    }
}

// 绘制媒体页面 | Draw media page
void draw_media_page()
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);
    
    // 绘制功能按钮 | Draw function buttons
    bar1(100,190,200,260,0xC618); // 拨号按钮 | Dial button
    bar1(100,290,200,360,0xC618); // 通讯录按钮 | Contact button
    bar1(433,190,533,260,0xC618); // 音乐按钮 | Music button
    bar1(433,290,533,360,0xC618); // 音响按钮 | Sound button
    
    // 添加按钮文字 | Add button labels
    puthz(130, 215, "拨号",24,30,0x000000); // 拨号 | Dial
    puthz(130, 315, "通讯",24,30,0x000000); // 通讯 | Contact
    puthz(463, 215, "音乐",24,30,0x000000); // 音乐 | Music
    puthz(463, 315, "音响",24,30,0x000000); // 音响 | Sound
}