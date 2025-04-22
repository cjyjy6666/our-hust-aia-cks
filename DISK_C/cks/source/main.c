#include <allfunc.h>  // 包含所有功能头文件 | Include all function headers

void main()
{      
    CarStatus state= {0};  // 车辆状态结构体初始化 | Initialize car status structure
    int puge = 0;          // 页面状态标识符 | Page state identifier
    init_car_status(&state); // 初始化车辆状态 | Initialize car status
    SetSVGA64k();          // 设置SVGA 64K色图形模式 | Set SVGA 64K color graphics mode
    
    mouse_init();          // 初始化鼠标 | Initialize mouse
    
    while (1)             // 主循环 | Main loop
    {
        switch (puge)     // 根据当前页面状态切换 | Switch based on current page state
        {
        case 0:           // 欢迎页面 | Welcome page
            welcome(&state,&puge);
            break;
        case 2:           // 主控制页面 | Main control page
            mainpage(&state,&puge);
            break;
        case 3:           // 车灯控制 | Light control
            light(&state,&puge);
            break;
        case 4:           // 空调控制 | AC control
            ac(&state,&puge);
            break;
        case 5:           // 自动导航 | Auto guidance
            autoguide(&state,&puge);
            break;
        case 6:           // 雨刷控制 | Wiper control
            wiper(&state,&puge);
            break;
        case 7:           // 驾驶模式 | Driving mode
            drive(&state,&puge);
            break;
        case 8:           // 媒体控制 | Media control
            draw_mainpage(&state);  // 绘制主页面背景 | Draw main page background
            media(&state,&puge);    // 显示媒体界面 | Show media interface
            break;
        case 9:           // 电话功能 | Phone function
            draw_mainpage(&state);
            phone(&state,&puge);
            break;
        case 10:          // 联系人 | Contacts
            draw_mainpage(&state);
            contact(&state,&puge);
            break;
        case 11:          // 音乐播放 | Music player
            draw_mainpage(&state);
            music(&state,&puge);
            break;
        case 12:          // 音响控制 | Sound system control
            draw_mainpage(&state);
            sounder(&state,&puge);
            break;
        case 13:          // 座椅调节 | Seat adjustment
            chair(&state,&puge);
            break;
        default:          // 默认情况 | Default case
            break;
        }
    }
    CloseSVGA();         // 关闭SVGA图形模式 | Close SVGA graphics mode
}
