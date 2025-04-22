#include"allfunc.h"

// 音乐播放器主函数 | Main function for music player
void music(CarStatus *state, int *puge)
{
    char mus[7][15] = {'\0'}; // 存储歌曲名数组 | Array to store song names (max 13 chars)
    const int LINES = count_music(); // 获取总行数 | Get total lines
    int pos = 0; // 当前显示的第一行位置 | Position of first line to show
    int select = 0; // 当前选中的行 | Selected line
    int i;
    
    read_music(mus, pos); // 读取音乐列表 | Read music list
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_music_page(state); // 绘制音乐页面 | Draw music page
    display_music(mus, select); // 显示音乐列表 | Display music list
    mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor
        
        if(state->media_s.mus_ord == 0) {
            button2(433,190,533,260,"顺序",&state->button_s.shunxu); // 顺序播放 | Order playback

        }
        
        else if(state->media_s.mus_ord == 1) {
            button2(433,190,533,260,"乱序",&state->button_s.luanxu); // 乱序播放 | Shuffle playback
            
        }
        else if(state->media_s.mus_ord == 2) {
            button2(433,190,533,260,"循环",&state->button_s.xunhuan1); // 循环播放 | Loop playback
        }
    
        // 设置播放/暂停按钮初始状态 | Set initial play/pause button state
        if(state->media_s.music == -1) {
            button2(433,290,533,360,"播放",&state->button_s.bofang); // 播放 | Play
        }
        else {
            button2(433,290,533,360,"暂停",&state->button_s.zanting); // 暂停 | Pause
        }
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 8; // 返回媒体页面 | Return to media page
            break;
        }
        
        // 向上滚动按钮 | Scroll up button
        if (mouse_press(270,60,300,95) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            
            if(pos > 0) {
                pos--;
                select++;
                read_music(mus, pos); // 重新读取音乐列表 | Re-read music list
                display_music(mus, select); // 更新显示 | Update display
            }
        }
        
        // 向下滚动按钮 | Scroll down button
        if (mouse_press(270,410-95,300,410-60) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            if(pos < LINES-7) {
                pos++;
                select--;
                read_music(mus, pos);
                display_music(mus, select);
            }
        }
        
        // 播放模式按钮 | Play mode button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 切换播放模式 | Toggle play mode
            if(state->media_s.mus_ord == 0) { // 顺序->乱序 | Order->Shuffle
                state->media_s.mus_ord = 1;
                bar1(434,191,532,259,0xC618);
                puthz(463, 215, "乱序",24,30,0x000000);
            }
            else if(state->media_s.mus_ord == 1) { // 乱序->循环 | Shuffle->Loop
                state->media_s.mus_ord = 2;
                bar1(434,191,532,259,0xC618);
                puthz(463, 215, "循环",24,30,0x000000);
            }
            else if(state->media_s.mus_ord == 2) { // 循环->顺序 | Loop->Order
                state->media_s.mus_ord = 0;
                bar1(434,191,532,259,0xC618);
                puthz(463, 215, "顺序",24,30,0x000000);
            }
        }
        
        // 播放/暂停按钮 | Play/Pause button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            // 切换播放状态 | Toggle play state
            if(state->media_s.music == -1) { // 如果未播放 | If not playing
                state->media_s.music = select + pos; // 播放选中歌曲 | Play selected song
            }
            else {
                state->media_s.music = -1; // 暂停播放 | Pause playing
            }
            
            // 更新按钮显示 | Update button display
            if(state->media_s.music == -1) {
                bar1(434,291,532,359,0xC618);
                puthz(463, 315, "播放",24,30,0x000000);
            }
            else {
                bar1(434,291,532,359,0xC618);
                puthz(463, 315, "暂停",24,30,0x000000);
            }
        }
        
        // 歌曲选择 | Song selection
        for(i = 0; i < 7; i++) {
            if (mouse_press(20,65+40*i,250,105+40*i) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                
                select = i; // 更新选中行 | Update selected line
                display_music(mus, select); // 更新显示 | Update display
                state->media_s.music = select; // 播放选中歌曲 | Play selected song
                
                // 更新播放按钮显示 | Update play button display
                if(state->media_s.music == -1) {
                    bar1(434,291,532,359,0x0085);
                    puthz(463, 315, "播放",24,30,0xFFFFFF);
                }
                else {
                    bar1(434,291,532,359,0x0085);
                    puthz(463, 315, "暂停",24,30,0xFFFFFF);
                }
            }
        }
    }
}

// 绘制音乐页面 | Draw music page
void draw_music_page(CarStatus *state)
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);

    // 绘制功能按钮 | Draw function buttons
    bar1(433,190,533,260,0xC618); // 播放模式按钮 | Play mode button
    bar1(433,290,533,360,0xC618); // 播放/暂停按钮 | Play/Pause button

    // 设置播放模式按钮初始状态 | Set initial play mode button state
    if(state->media_s.mus_ord == 0) {
        bar1(434,191,532,259,0xC618);
        puthz(463, 215, "顺序",24,30,0x000000); // 顺序 | Order
    }
    else if(state->media_s.mus_ord == 1) {
        bar1(434,191,532,259,0xC618);
        puthz(463, 215, "乱序",24,30,0x000000); // 乱序 | Shuffle
    }
    else if(state->media_s.mus_ord == 2) {
        bar1(434,191,532,259,0xC618);
        puthz(463, 215, "循环",24,30,0x000000); // 循环 | Loop
    }

    // 设置播放/暂停按钮初始状态 | Set initial play/pause button state
    if(state->media_s.music == -1) {
        bar1(434,291,532,359,0xC618);
        puthz(463, 315, "播放",24,30,0x000000); // 播放 | Play
    }
    else {
        bar1(434,291,532,359,0xC618);
        puthz(463, 315, "暂停",24,30,0x000000); // 暂停 | Pause
    }

    // 绘制音乐列表区域 | Draw music list area
    bar2(20,60,250,350,0xFFFFFF);
    bar2(19,59,251,351,0xFFFFFF);
    
    // 绘制向上箭头 | Draw up arrow
    Line2(285,60,270,80,0xFFFFFF);
    Line2(270,80,278,80,0xFFFFFF);
    Line2(278,80,278,95,0xFFFFFF);
    Line2(278,95,292,95,0xFFFFFF);
    Line2(292,95,292,80,0xFFFFFF);
    Line2(292,80,300,80,0xFFFFFF);
    Line2(300,80,285,60,0xFFFFFF);
 
    // 绘制向下箭头 | Draw down arrow
    Line2(285,410-60,270,410-80,0xFFFFFF);
    Line2(270,410-80,278,410-80,0xFFFFFF);
    Line2(278,410-80,278,410-95,0xFFFFFF);
    Line2(278,410-95,292,410-95,0xFFFFFF);
    Line2(292,410-95,292,410-80,0xFFFFFF);
    Line2(292,410-80,300,410-80,0xFFFFFF);
    Line2(300,410-80,285,410-60,0xFFFFFF);
    
    // 绘制音乐列表分隔线 | Draw music list dividers
    Line2(20,65,250,65,0xFFFFFF);
    Line2(20,105,250,105,0xFFFFFF);
    Line2(20,145,250,145,0xFFFFFF);
    Line2(20,185,250,185,0xFFFFFF);
    Line2(20,225,250,225,0xFFFFFF);
    Line2(20,265,250,265,0xFFFFFF);
    Line2(20,305,250,305,0xFFFFFF);
    Line2(20,345,250,345,0xFFFFFF);
    
    // 绘制音乐列表背景 | Draw music list background
    bar1(21,66,249,104,0x0085);
    bar1(21,106,249,144,0x0085);
    bar1(21,146,249,184,0x0085);
    bar1(21,186,249,224,0x0085);
    bar1(21,226,249,264,0x0085);
    bar1(21,266,249,304,0x0085);
    bar1(21,306,249,344,0x0085);
}

// 计算音乐文件行数 | Count music file lines
int count_music()
{
    FILE *fp;
    int total = 0;
    char buffer[15];
    fp = fopen("data\\music.txt","r"); // 打开音乐文件 | Open music file
    
    while(fgets(buffer, sizeof(buffer), fp)) {
        total++; // 统计行数 | Count lines
    }
    
    fclose(fp);
    return total;
}

// 读取音乐列表 | Read music list
void read_music(char mus[7][15], int pos)
{
    FILE *fp;
    int i, j;
    int newline_pos;
    char buffer[15];
    
    fp = fopen("data\\music.txt","r");
    rewind(fp); // 重置文件指针 | Reset file pointer
    
    // 跳过前面的行 | Skip previous lines
    for(i = 0; i < pos; i++) {
        fgets(buffer, sizeof(buffer), fp);
    }
    
    // 读取7行音乐 | Read 7 lines of music
    for(j = pos; j < pos + 7; j++) {
        if(fgets(buffer, sizeof(buffer), fp)) {
            // 删除换行符 | Remove newline
            newline_pos = -1;
            for(i = 0; i < sizeof(buffer) + 1; i++) {
                if(buffer[i] == '\n') {
                    newline_pos = i;
                    break;
                }
            }
            
            if(newline_pos != -1) {
                buffer[newline_pos] = '\0'; // 替换换行符为结束符 | Replace newline with terminator
            }
            else {
                buffer[12] = '\0'; // 如果没有换行符 | If no newline
            }
            
            strcpy(mus[j - pos], buffer); // 复制歌曲名 | Copy song name
        }
        else {
            mus[j - pos][0] = '\0'; // 如果没有更多行 | If no more lines
        }
    }
    
    fclose(fp);
}

// 显示音乐列表 | Display music list
void display_music(char mus[7][15], int select)
{
    int i;
    for(i = 0; i < 7; i++) {
        if(mus[i][0] != '\0') { // 如果有歌曲名 | If song name exists
            bar1(21,66+i*40,249,104+i*40,0x0085);
            prt_hz24_asc32(25,69+i*40,mus[i],0xFFFFFF,"HZK\\Hzk24f"); // 显示歌曲名 | Display song name
        }
        else { // 如果没有歌曲名 | If no song name
            bar1(21,66+i*40,249,104+i*40,0x0085);
        }
        
        if(i == select) { // 如果是选中行 | If selected line
            mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
            bar1(21,66+i*40,249,104+i*40,0x7FFF); // 高亮选中行 | Highlight selected line
            prt_hz24_asc32(25,69+i*40,mus[i],0xFFFFFF,"HZK\\Hzk24f"); // 显示歌曲名 | Display song name
            mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor
        }
    }
}