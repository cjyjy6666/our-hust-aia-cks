#include"allfunc.h"
#define PI 3.1415926

// 显示所有状态 | Display all status
void show_all(CarStatus *state)
{
    show_light(state);    // 显示车灯状态 | Display light status
    show_ac(state);       // 显示空调状态 | Display AC status
    show_wiper(state);    // 显示雨刷状态 | Display wiper status
    show_drive(state);    // 显示驾驶状态 | Display drive status
    show_phone(state);    // 显示电话状态 | Display phone status
    show_music(state);    // 显示音乐状态 | Display music status
}

// 显示车灯状态 | Display light status
void show_light(CarStatus *state)
{
    light_blink(state); // 处理转向灯闪烁 | Handle turn signal blinking
    
    // 远光灯显示 | Far light display
    if(state->light_s.far_light)
        Readbmp64k(670,500,"bmp\\far.bmp");
    else
        bar1(670,500,704,522,0x0000);
        
    // 近光灯显示 | Near light display
    if(state->light_s.near_light)
        Readbmp64k(670,532,"bmp\\near.bmp");
    else
        bar1(670,532,704,556,0x0000);
    
    // 雾灯显示 | Fog light display
    if(state->light_s.fog) {
        Readbmp64k(670,569,"bmp\\fog1.bmp");
        Readbmp64k(704,566,"bmp\\fog2.bmp");
    } else {
        bar1(670,569,704,591,0x0000);
        bar1(704,566,738,591,0x0000);
    }
    
    // 左转向灯显示 | Left turn signal display
    if(state->light_s.left_blink_state)
        Readbmp64k(670,452,"bmp\\left.bmp");
    else
        bar1(670,452,704,494,0x0000);
    
    // 右转向灯显示 | Right turn signal display
    if(state->light_s.right_blink_state)
        Readbmp64k(956,452,"bmp\\right.bmp");
    else
        bar1(956,452,990,493,0x0000);
}

// 转向灯闪烁控制 | Turn signal blink control
void light_blink(CarStatus *state)
{
    if(check_timer_expire(&(state->timer.light_time), CLOCKS_PER_SEC/2)) {
        if(state->light_s.left)
            state->light_s.left_blink_state ^= 1; // 切换左转向灯状态 | Toggle left turn signal
        else
            state->light_s.left_blink_state = 0;
            
        if(state->light_s.right)
            state->light_s.right_blink_state ^= 1; // 切换右转向灯状态 | Toggle right turn signal
        else
            state->light_s.right_blink_state = 0;
    }
}

// 显示空调状态 | Display AC status
void show_ac(CarStatus *state)
{
    char cur_temp[5] = {'\0'};
    sprintf(cur_temp,"%d℃",state->ac_s.current_temp);
    prt_hz24_asc32(40,667,cur_temp,0xFC44,"HZK\\Hzk24f"); // 显示当前温度 | Display current temperature
    
    // 内循环显示 | Circulate display
    if(state->ac_s.circulate)
        Readbmp64k(710,452,"bmp\\accir.bmp");
    else
        bar1(710,452,744,472,0x0000);
    
    // 新鲜空气显示 | Fresh air display
    if(state->ac_s.fresh_air)
        Readbmp64k(710,532,"bmp\\acair.bmp");
    else
        bar1(710,532,744,549,0x0000);
    
    // 除雾显示 | Defog display
    if(state->ac_s.defog)
        Readbmp64k(710,500,"bmp\\acfog.bmp");
    else
        bar1(710,500,744,526,0x0000);

    temp_change(state); // 温度变化处理 | Handle temperature change
}

// 显示雨刷状态 | Display wiper status
void show_wiper(CarStatus *state)
{
    // 快速雨刷显示 | Fast wiper display
    if(state->wiper_s.cur_wip == 2)
        Readbmp64k(930,700,"bmp\\w1.bmp");
    else
        bar1(930,700,990,747,0x0000);
    
    // 慢速雨刷显示 | Slow wiper display
    if(state->wiper_s.cur_wip == 1)
        Readbmp64k(930,650,"bmp\\w2.bmp");
    else
        bar1(930,650,990,694,0x0000);
}

// 显示驾驶状态 | Display drive status
void show_drive(CarStatus *state)
{
    int xs, ys, xs1, ys1, xn, yn, xn1, yn1;
    
    // 计算速度表指针位置 | Calculate speedometer needle position
    xs = (int)(829-130*cos(state->drive_s.angle_s*PI/180));
    ys = (int)(400-130*sin(state->drive_s.angle_s*PI/180));
    xs1 = (int)(829-50*cos(state->drive_s.angle_s*PI/180));
    ys1 = (int)(400-50*sin(state->drive_s.angle_s*PI/180));
    
    // 计算转速表指针位置 | Calculate tachometer needle position
    xn = (int)(829-130*cos(state->drive_s.angle_n*PI/180));
    yn = (int)(194-130*sin(state->drive_s.angle_n*PI/180));
    xn1 = (int)(829-50*cos(state->drive_s.angle_n*PI/180));
    yn1 = (int)(194-50*sin(state->drive_s.angle_n*PI/180));
    
    // 绘制仪表指针 | Draw gauge needles
    Line2(xs1,ys1,xs,ys,0xF800); // 速度表指针 | Speedometer needle
    Line2(xn1,yn1,xn,yn,0xF800); // 转速表指针 | Tachometer needle
    
    // 前进模式显示 | Forward mode display
    if(state->drive_s.forward==1 && state->drive_s.sport==0 && state->drive_s.comfort==0 && state->drive_s.view==0) {
        Put_Asc16_Size(800,460,2,2,'D',0xF800);
        needle_s(state,100); // 设置速度表指针 | Set speedometer needle
        if(!state->drive_s.once_f) {
            if(n_change(state))
                state->drive_s.once_f=1;
        }
    }
    
    // 后退模式显示 | Back mode display
    if(state->drive_s.back==1) {
        Put_Asc16_Size(800,460,2,2,'R',0xF800);
        needle_s(state,60);
        if(!state->drive_s.once_b) {
            if(n_change(state))
                state->drive_s.once_b=1;
        }
    }
    
    // 停车模式显示 | Park mode display
    if(state->drive_s.park==1) {
        Put_Asc16_Size(800,460,2,2,'P',0xF800);
        needle_s(state,20);
        if(!state->drive_s.once_p) {
            if(n_change(state))
                state->drive_s.once_p=1;
        }
    }
    
    // 运动模式显示 | Sport mode display
    if(state->drive_s.sport==1) {
        Put_Asc16_Size(800,460,2,2,'S',0xF800);
        needle_s(state,150);
        if(!state->drive_s.once_s) {
            if(n_change(state))
                state->drive_s.once_s=1;
        }
    }
    
    // 舒适模式显示 | Comfort mode display
    if(state->drive_s.comfort==1) {
        Put_Asc16_Size(800,460,2,2,'D',0xF800);
        needle_s(state,80);
    }
    
    // 观光模式显示 | View mode display
    if(state->drive_s.view==1) {
        Put_Asc16_Size(800,460,2,2,'D',0xF800);
        needle_s(state,40);
    }
}

// 显示电话状态 | Display phone status
void show_phone(CarStatus *state)
{
    char call_str[15] = {'\0'};
    if(state->media_s.on_call) {
        if(check_timer_expire(&(state->timer.call_time), CLOCKS_PER_SEC)) {
            state->media_s.call_second++;
            bar1(660,700,860,748,0x0000);
            sprintf(call_str,"通话中:%d秒",state->media_s.call_second); // 显示通话时间 | Display call time
            prt_hz24_asc32(660,700,call_str,0xFC44,"HZK\\Hzk24f");
        }
    } else {
        bar1(660,700,860,748,0x0000);
    }
}

// 显示音乐状态 | Display music status
void show_music(CarStatus *state)
{
    char mus_name[15];
    char mus_str[30];
    int i, newline_pos;
    static int sec = 75; // 歌曲剩余秒数 | Song remaining seconds
    static int cur_music = -1; // 当前播放歌曲 | Current playing song
    static FILE *fp;
    static int file_init = 0;
    static int TOTLE = -1; // 歌曲总数 | Total songs

    if(TOTLE == -1) {
        TOTLE = count_music(); // 获取歌曲总数 | Get total songs
    }
    
    // 读取歌曲名称 | Read song name
    if(!file_init) {
        fp = fopen("data\\music.txt","r");
        if(fp == NULL) {
            fclose(fp);
            return;
        }
        file_init = 1;
    } else {
        rewind(fp);
    }
    
    for(i = 0; i < state->media_s.music + 1; i++) {
        if(fgets(mus_name, sizeof(mus_name), fp) == NULL) {
            fclose(fp);
            return;
        }
    }
    
    // 删除换行符 | Remove newline
    newline_pos = -1;
    for(i = 0; i < sizeof(mus_name) + 1; i++) {
        if(mus_name[i] == '\n') {
            newline_pos = i;
            break;
        }
    }
    if(newline_pos != -1) {
        mus_name[newline_pos] = '\0';
    } else {
        mus_name[14] = '\0';
    }

    // 显示歌曲名称和时间 | Display song name and time
    if(state->media_s.music != -1) {
        if(cur_music != state->media_s.music) {
            sec = 75;
            cur_music = state->media_s.music;
        }
        if(check_timer_expire(&(state->timer.music_time), CLOCKS_PER_SEC)) {
            sec--;
            bar1(660,650,920,700,0x0000);
            sprintf(mus_str,"%s:%d:%d",mus_name,sec/60,sec%60); // 格式化时间显示 | Format time display
            prt_hz24_asc32(660,650,mus_str,0xFC44,"HZK\\Hzk24f");
        }
        if(sec <= 0) {
            sec = 75;
            switch(state->media_s.mus_ord) {
                case 0: // 顺序播放 | Order play
                    state->media_s.music = (state->media_s.music + 1) % TOTLE;
                    break;
                case 1: // 随机播放 | Shuffle play
                    state->media_s.music = random(TOTLE);
                    break;
                case 2: // 单曲循环 | Single loop
                    break;
            }
        }
    } else if(cur_music != -1) {
        bar1(660,650,920,700,0x0000);
    }
    
    if(state->media_s.music == -1 && fp != NULL) {
        fclose(fp);
        file_init = 0;
    }
}