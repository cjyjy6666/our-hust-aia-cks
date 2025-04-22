#include"allfunc.h"


void chair(CarStatus *state, int *puge) {
    mouse_off(&mouse);    // 关闭鼠标显示 | Hide mouse cursor
    draw_chair_page(state->chair_s.x1,state->chair_s.y1,state->chair_s.x2,state->chair_s.y2);       // 绘制空调页面 | Draw AC control page
    mouse_on(mouse);      // 开启鼠标显示 | Show mouse cursor

    while (1) {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor

        button2(60,335,160,405,"前",&state->button_s.qian);
        button2(200,335,300,405,"后",&state->button_s.hou);
        button2(340,335,440,405,"左",&state->button_s.zuo);
        button2(480,335,580,405,"右",&state->button_s.you);
        button2(200,480,300,550,"升",&state->button_s.shang);
        button2(340,480,440,550,"降",&state->button_s.xia);
        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 2; // 返回主页面 | Return to main page
            break;
        }

        if(mouse_press(60,335,160,405) == 1&&state->chair_s.y1>105&&state->chair_s.x2>350){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.y1 -= 10;
            state->chair_s.x2 -= 10;
            draw_chair1(state->chair_s.x1,state->chair_s.y1);
            draw_chair2(state->chair_s.x2,state->chair_s.y2);

        }

        if(mouse_press(200,335,300,405) == 1&&state->chair_s.y1<210&&state->chair_s.x2<520){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.y1 += 10;
            state->chair_s.x2 += 10;
            draw_chair1(state->chair_s.x1,state->chair_s.y1);
            draw_chair2(state->chair_s.x2,state->chair_s.y2);
            
        }

        if(mouse_press(340,335,440,405) == 1&&state->chair_s.x1>140){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.x1 -= 10;
            draw_chair1(state->chair_s.x1,state->chair_s.y1);
            
        }

        if(mouse_press(480,335,580,405) == 1&&state->chair_s.x1<200){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.x1 += 10;
            draw_chair1(state->chair_s.x1,state->chair_s.y1);
        }

        if(mouse_press(200,480,300,550) == 1&&state->chair_s.y2>150){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.y2 -= 10;
            draw_chair2(state->chair_s.x2,state->chair_s.y2);
            
        }

        if(mouse_press(340,480,440,550) == 1&&state->chair_s.y2<230){
            do{
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while((mouse.key & 1) == 1);
            state->chair_s.y2 += 10;
            draw_chair2(state->chair_s.x2,state->chair_s.y2); 
        }



    }

}

void draw_chair_page(int x1,int y1,int x2,int y2){
    bar1(20,23,616,306,0x000000);
    Line2(320,23,320,306,0xFFFFFF);

    //按钮
    bar1(60,335,160,405,0xC618);
    bar1(200,335,300,405,0xC618);
    bar1(340,335,440,405,0xC618);
    bar1(480,335,580,405,0xC618);
    bar1(200,480,300,550,0xC618);
    bar1(340,480,440,550,0xC618);

    //文字
    puthz(90,360,"前",24,30,0x000000);
    puthz(230,360,"后",24,30,0x000000);
    puthz(370,360,"左",24,30,0x000000);
    puthz(510,360,"右",24,30,0x000000);
    puthz(230,505,"升",24,30,0x000000);
    puthz(370,505,"降",24,30,0x000000);

    draw_chair1(x1,y1);
    draw_chair2(x2,y2);

     // 绘制返回按钮 | Draw back button
     Line2(603,600,633,600,0xFFFFFF);
     Line2(603,600,603,630,0xFFFFFF);
     Line2(603,600,633,630,0xFFFFFF);
     Line2(633,600,603,630,0xFFFFFF);



}

void draw_chair1(int x1,int y1){
    bar1(20,23,317,306,0x000000);
    bar2(x1-50,y1-40,x1+50,y1+40,0xFFFFFF);
    bar2(x1-80,y1-45,x1-55,y1+40,0xFFFFFF);
    bar2(x1+55,y1-45,x1+80,y1+40,0xFFFFFF);
    bar2(x1-70,y1+45,x1+70,y1+70,0xFFFFFF);

}

void draw_chair2(int x2,int y2){
    bar1(323,23,616,306,0x000000);
    Line2(x2+40,y2,x2+40,y2-90,0xFFFFFF);
    Line2(x2+60,y2,x2+60,y2-90,0xFFFFFF);
    Line2(x2+40,y2,x2+60,y2,0xFFFFFF);
    Line2(x2+40,y2-90,x2+60,y2-90,0xFFFFFF);
    bar2(x2-70,y2-30,x2+40,y2-10,0xFFFFFF);
    bar2(x2-60,y2+10,x2+60,280,0xFFFFFF);
        

    
}