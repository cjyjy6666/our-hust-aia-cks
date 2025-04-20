#include"allfunc.h"

// 联系人管理主函数 | Main function for contact management
void contact(CarStatus *state, int *puge)
{
    char num[7][13] = {'\0'}; // 存储联系人号码数组 | Array to store contact numbers
    const int LINES = count_lines(); // 获取总行数 | Get total lines
    int pos = 0; // 当前显示的第一行位置 | Position of first line to show
    int select = 0; // 当前选中的行 | Selected line
    int i;
    
    read_contact(num, pos); // 读取联系人 | Read contacts
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_contact_page(state); // 绘制联系人页面 | Draw contact page
    display_contact(num, select); // 显示联系人 | Display contacts
    mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor
        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 8;
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
                read_contact(num, pos); // 重新读取联系人 | Re-read contacts
                display_contact(num, select); // 更新显示 | Update display
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
                read_contact(num, pos);
                display_contact(num, select);
            }
        }
        
        // 删除按钮 | Delete button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            del_num(num, select); // 删除选中联系人 | Delete selected contact
            read_contact(num, pos);
            display_contact(num, select);
        }
        
        // 拨打/挂断按钮 | Call/Hang up button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->media_s.on_call ^= 1; // 切换通话状态 | Toggle call state
            state->media_s.call_second = 0; // 重置通话时间 | Reset call time
            
            if(state->media_s.on_call) { // 如果是拨打状态 | If calling
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "挂断",24,30,0xF800); // 显示挂断 | Show hang up
            }
            else { // 如果是挂断状态 | If hanging up
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "拨打",24,30,0xFFFFFF); // 显示拨打 | Show call
            }
        }
        
        // 联系人选择 | Contact selection
        for(i = 0; i < 7; i++) {
            if (mouse_press(20,65+40*i,250,105+40*i) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                
                select = i; // 更新选中行 | Update selected line
                display_contact(num, select); // 更新显示 | Update display
            }
        }
    }
}

// 绘制联系人页面 | Draw contact page
void draw_contact_page(CarStatus *state)
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);

    // 绘制功能按钮 | Draw function buttons
    bar2(433,190,533,260,0xFFFFFF); // 拨打/挂断按钮 | Call/Hang up button
    bar2(433,290,533,360,0xFFFFFF); // 删除按钮 | Delete button
    
    // 根据通话状态设置按钮样式 | Set button style based on call state
    if(state->media_s.on_call) {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "挂断",24,30,0xF800); // 挂断 | Hang up
    }
    else {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "拨打",24,30,0xFFFFFF); // 拨打 | Call
    }
    
    puthz(463, 315, "删除",24,30,0xFFFFFF); // 删除 | Delete
    
    // 绘制联系人列表边框 | Draw contact list border
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
    
    // 绘制联系人列表分隔线 | Draw contact list dividers
    Line2(20,65,250,65,0xFFFFFF);
    Line2(20,105,250,105,0xFFFFFF);
    Line2(20,145,250,145,0xFFFFFF);
    Line2(20,185,250,185,0xFFFFFF);
    Line2(20,225,250,225,0xFFFFFF);
    Line2(20,265,250,265,0xFFFFFF);
    Line2(20,305,250,305,0xFFFFFF);
    Line2(20,345,250,345,0xFFFFFF);
    
    // 绘制联系人列表背景 | Draw contact list background
    bar1(21,66,249,104,0x0085);
    bar1(21,106,249,144,0x0085);
    bar1(21,146,249,184,0x0085);
    bar1(21,186,249,224,0x0085);
    bar1(21,226,249,264,0x0085);
    bar1(21,266,249,304,0x0085);
    bar1(21,306,249,344,0x0085);
}

// 计算文件行数 | Count file lines
int count_lines()
{
    FILE *fp;
    int total = 0;
    char buffer[13];
    fp = fopen("data\\phone.dat","r"); // 打开联系人文件 | Open contact file
    
    while(fgets(buffer, sizeof(buffer), fp)) {
        total++; // 统计行数 | Count lines
    }
    
    fclose(fp);
    return total;
}

// 读取联系人 | Read contacts
void read_contact(char num[7][13], int pos)
{
    FILE *fp;
    int i, j;
    int newline_pos;
    char buffer[13];
    
    fp = fopen("data\\phone.dat","r");
    rewind(fp); // 重置文件指针 | Reset file pointer
    
    // 跳过前面的行 | Skip previous lines
    for(i = 0; i < pos; i++) {
        fgets(buffer, sizeof(buffer), fp);
    }
    
    // 读取7行联系人 | Read 7 lines of contacts
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
            
            strcpy(num[j - pos], buffer); // 复制号码 | Copy number
        }
        else {
            num[j - pos][0] = '\0'; // 如果没有更多行 | If no more lines
        }
    }
    
    fclose(fp);
}

// 显示联系人 | Display contacts
void display_contact(char num[7][13], int select)
{
    int i;
    for(i = 0; i < 7; i++) {
        if(num[i][0] != '\0') { // 如果有号码 | If number exists
            bar1(21,66+i*40,249,104+i*40,0x0085);
            put_asc16_size(25,69+i*40,2,2,num[i],0xFFFFFF); // 显示号码 | Display number
        }
        else { // 如果没有号码 | If no number
            bar1(21,66+i*40,249,104+i*40,0x0085);
        }
        
        if(i == select) { // 如果是选中行 | If selected line
            mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
            bar1(21,66+i*40,249,104+i*40,0x7FFF); // 高亮选中行 | Highlight selected line
            put_asc16_size(25,69+i*40,2,2,num[i],0xFFFFFF); // 显示号码 | Display number
            mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor
        }
    }
}

// 删除联系人 | Delete contact
void del_num(char num[7][13], int select)
{
    FILE *fp;
    FILE *temp;
    int newline_pos;
    char buffer[13];
    int i;
    
    fp = fopen("data\\phone.dat","r"); // 打开原文件 | Open original file
    temp = fopen("data\\temp.dat","w"); // 创建临时文件 | Create temp file
    
    while(fgets(buffer, sizeof(buffer), fp)) {
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
        
        if(strcmp(buffer, num[select]) != 0) { // 如果不是要删除的行 | If not the line to delete
            fputs(buffer, temp); // 写入临时文件 | Write to temp file
            fputs("\n", temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    remove("data\\phone.dat"); // 删除原文件 | Delete original file
    rename("data\\temp.dat","data\\phone.dat"); // 重命名临时文件 | Rename temp file
}