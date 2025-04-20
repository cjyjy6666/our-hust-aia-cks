#include"allfunc.h"

// 电话拨号主函数 | Main function for phone dialing
void phone(CarStatus *state, int *puge)
{
    FILE *fp;
    static char ph_num[13] = {'\0'}; // 存储电话号码 | Store phone number
    static int num_len = 0; // 当前号码长度 | Current number length
    int exists = 0; // 号码是否已存在 | Whether number exists
    char buffer[13]; // 读取缓冲区 | Read buffer
    int newline_pos = -1; // 换行符位置 | Newline position
    int i; // 循环变量 | Loop variable
    
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    draw_phone_page(state); // 绘制电话页面 | Draw phone page
    mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor
        
        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            *puge = 8; // 返回媒体页面 | Return to media page
            break;
        }
        
        key_det(ph_num, &num_len); // 检测按键输入 | Detect key input
        
        // 拨打/挂断按钮 | Call/Hang up button
        if (mouse_press(433,190,533,260) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1); // 等待鼠标释放 | Wait for mouse release
            
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
        
        // 保存号码按钮 | Save number button
        if (mouse_press(433,290,533,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            fp = fopen("data\\phone.dat","a+"); // 打开电话簿文件 | Open phone book file
            
            // 检查号码是否已存在 | Check if number already exists
            exists = 0;
            rewind(fp);
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
                
                if(strcmp(buffer, ph_num) == 0) {
                    exists = 1;
                    break;
                }
            }
            
            // 保存号码 | Save number
            if(!exists) {
                fprintf(fp, "%s\n", ph_num); // 写入文件 | Write to file
                bar1(241,91,619,149,0x0085);
                prt_hz24_asc32(322,104,"保存成功",0xFC44,"HZK\\Hzk24f"); // 显示保存成功 | Show save success
            }
            else {
                bar1(241,91,619,149,0x0085);
                prt_hz24_asc32(322,104,"号码已存在",0xFC44,"HZK\\Hzk24f"); // 显示号码已存在 | Show number exists
            }
            
            fclose(fp);
            num_len = 0; // 重置号码长度 | Reset number length
            ph_num[0] = '\0'; // 清空号码 | Clear number
        }
    }
}

// 绘制电话页面 | Draw phone page
void draw_phone_page(CarStatus *state)
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);

    // 绘制数字键盘 | Draw number pad
    Circle(60,130,20,0xFFFFFF);  // 1
    Circle(130,130,20,0xFFFFFF); // 2
    Circle(200,130,20,0xFFFFFF); // 3
    Circle(60,200,20,0xFFFFFF);  // 4
    Circle(130,200,20,0xFFFFFF); // 5
    Circle(200,200,20,0xFFFFFF); // 6
    Circle(60,270,20,0xFFFFFF);  // 7
    Circle(130,270,20,0xFFFFFF); // 8
    Circle(200,270,20,0xFFFFFF); // 9
    Circle(60,340,20,0xFFFFFF);  // #
    Circle(130,340,20,0xFFFFFF); // 0
    Circle(200,340,20,0xFFFFFF); // X (删除)

    // 绘制数字标签 | Draw number labels
    Put_Asc16_Size(50,114,2,2,'1',0xFFFFFF);
    Put_Asc16_Size(120,114,2,2,'2',0xFFFFFF);
    Put_Asc16_Size(190,114,2,2,'3',0xFFFFFF);
    Put_Asc16_Size(50,184,2,2,'4',0xFFFFFF);
    Put_Asc16_Size(120,184,2,2,'5',0xFFFFFF);
    Put_Asc16_Size(190,184,2,2,'6',0xFFFFFF);
    Put_Asc16_Size(50,254,2,2,'7',0xFFFFFF);
    Put_Asc16_Size(120,254,2,2,'8',0xFFFFFF);
    Put_Asc16_Size(190,254,2,2,'9',0xFFFFFF);
    Put_Asc16_Size(50,324,2,2,'#',0xFFFFFF);
    Put_Asc16_Size(120,324,2,2,'0',0xFFFFFF);
    Put_Asc16_Size(190,324,2,2,'X',0xFFFFFF);

    // 绘制功能按钮 | Draw function buttons
    bar2(433,190,533,260,0xFFFFFF); // 拨打/挂断 | Call/Hang up
    bar2(433,290,533,360,0xFFFFFF); // 保存号码 | Save number

    // 设置拨打/挂断按钮状态 | Set call/hang up button state
    if(state->media_s.on_call) {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "挂断",24,30,0xF800); // 挂断 | Hang up
    }
    else {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "拨打",24,30,0xFFFFFF); // 拨打 | Call
    }

    puthz(463, 315, "存号",24,30,0xFFFFFF); // 存号 | Save
    bar2(240,90,620,150,0xFC44); // 号码显示区域 | Number display area
    bar1(241,91,619,149,0x0085); // 号码显示背景 | Number display background
}

// 按键检测函数 | Key detection function
void key_det(char ph_num[13], int *num_len)
{
    int x; // 显示位置 | Display position
    
    if(*num_len < 12) { // 如果号码长度小于12 | If number length less than 12
        // 数字1按钮 | Number 1 button
        if (mouse_press(40,110,80,150) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '1'; // 添加数字1 | Add number 1
            ph_num[*num_len] = '\0'; // 添加结束符 | Add terminator
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2; // 计算显示位置 | Calculate display position
            put_asc16_size(x,104,2,2,ph_num,0xFC44); // 显示号码 | Display number
        }
        
        // 数字2按钮 | Number 2 button
        if (mouse_press(110,110,150,150) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '2';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // ... 其他数字按钮类似 (Other number buttons similar) ...
        
        // 删除按钮 | Delete button
        if(*num_len > 0) {
            if (mouse_press(180,320,220,360) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                ph_num[--(*num_len)] = '\0'; // 删除最后一个字符 | Delete last character
                bar1(241,91,619,149,0x0085);
                x = 240 + (380 - 16 * (*num_len)) / 2;
                put_asc16_size(x,104,2,2,ph_num,0xFC44);
            }
        }
    }
    else { // 如果号码长度达到限制 | If number length reaches limit
        bar1(241,91,619,149,0x0085);
        prt_hz24_asc32(322,104,"号码应为11位!",0xFC44,"HZK\\Hzk24f"); // 显示提示 | Show prompt
        while(mouse.key & 1) // 等待鼠标释放 | Wait for mouse release
            MouseGet(&mouse);
        *num_len = 0; // 重置号码长度 | Reset number length
        ph_num[0] = '\0'; // 清空号码 | Clear number
    }