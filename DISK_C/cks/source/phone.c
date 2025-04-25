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

        button2(433,290,533,360,"存号", &state->button_s.cunhao); // 保存号码按钮 | Save number button
        if(state->media_s.on_call) {
           button3(433,190,532,260,"挂断", &state->button_s.guaduan); // 挂断按钮 | Hang up button
        }
        else {
           button2(433,190,533,260,"拨打", &state->button_s.boda); // 拨打按钮 | Call button
        }
        button4(60,130,20,'1', &state->button_s.num1); // 数字按钮 | Number buttons
        button4(130,130,20,'2', &state->button_s.num2); // 数字按钮 | Number buttons
        button4(200,130,20,'3', &state->button_s.num3); // 数字按钮 | Number buttons
        button4(60,200,20,'4', &state->button_s.num4); // 数字按钮 | Number buttons
        button4(130,200,20,'5', &state->button_s.num5); // 数字按钮 | Number buttons
        button4(200,200,20,'6', &state->button_s.num6); // 数字按钮 | Number buttons
        button4(60,270,20,'7', &state->button_s.num7); // 数字按钮 | Number buttons
        button4(130,270,20,'8', &state->button_s.num8); // 数字按钮 | Number buttons
        button4(200,270,20,'9', &state->button_s.num9); // 数字按钮 | Number buttons
        button4(60,340,20,'#', &state->button_s.num); // 数字按钮 | Number buttons
        button4(130,340,20,'0', &state->button_s.num0); // 数字按钮 | Number buttons
        button4(200,340,20,'X', &state->button_s.numx); // 数字按钮 | Number buttons
        button5(603,600,633,630,&state->button_s.xxx); // 返回按钮 | Back button



        
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
                bar1(434,191,532,259,0xC618);
                puthz(463, 215, "挂断",24,30,0xF800); // 显示挂断 | Show hang up
            }
            else { // 如果是挂断状态 | If hanging up
                bar1(434,191,532,259,0xC618);
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
    Circlefill(60,130,20,0xC618);  // 1
    Circlefill(130,130,20,0xC618); // 2
    Circlefill(200,130,20,0xC618); // 3
    Circlefill(60,200,20,0xC618);  // 4
    Circlefill(130,200,20,0xC618); // 5
    Circlefill(200,200,20,0xC618); // 6
    Circlefill(60,270,20,0xC618);  // 7
    Circlefill(130,270,20,0xC618); // 8
    Circlefill(200,270,20,0xC618); // 9
    Circlefill(60,340,20,0xC618);  // #
    Circlefill(130,340,20,0xC618); // 0
    Circlefill(200,340,20,0xC618); // X (删除)

    // 绘制数字标签 | Draw number labels
    Put_Asc16_Size(50,114,2,2,'1',0x000000);
    Put_Asc16_Size(120,114,2,2,'2',0x000000);
    Put_Asc16_Size(190,114,2,2,'3',0x000000);
    Put_Asc16_Size(50,184,2,2,'4',0x000000);
    Put_Asc16_Size(120,184,2,2,'5',0x000000);
    Put_Asc16_Size(190,184,2,2,'6',0x000000);
    Put_Asc16_Size(50,254,2,2,'7',0x000000);
    Put_Asc16_Size(120,254,2,2,'8',0x000000);
    Put_Asc16_Size(190,254,2,2,'9',0x000000);
    Put_Asc16_Size(50,324,2,2,'#',0x000000);
    Put_Asc16_Size(120,324,2,2,'0',0x000000);
    Put_Asc16_Size(190,324,2,2,'X',0x000000);

    // 绘制功能按钮 | Draw function buttons
    bar1(433,190,533,260,0xC618); // 拨打/挂断 | Call/Hang up
    bar1(433,290,533,360,0xC618); // 保存号码 | Save number

    // 设置拨打/挂断按钮状态 | Set call/hang up button state
    if(state->media_s.on_call) {
        bar1(434,191,532,259,0xC618);
        puthz(463, 215, "挂断",24,30,0xF800); // 挂断 | Hang up
    }
    else {
        bar1(434,191,532,259,0xC618);
        puthz(463, 215, "拨打",24,30,0x000000); // 拨打 | Call
    }

    puthz(463, 315, "存号",24,30,0x000000); // 存号 | Save
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
            ph_num[(*num_len)++] = '1';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
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
        
        // 数字3按钮 | Number 3 button
        if (mouse_press(180,110,220,150) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '3';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字4按钮 | Number 4 button
        if (mouse_press(40,180,80,220) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '4';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字5按钮 | Number 5 button
        if (mouse_press(110,180,150,220) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '5';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字6按钮 | Number 6 button
        if (mouse_press(180,180,220,220) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '6';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字7按钮 | Number 7 button
        if (mouse_press(40,250,80,290) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '7';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字8按钮 | Number 8 button
        if (mouse_press(110,250,150,290) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '8';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字9按钮 | Number 9 button
        if (mouse_press(180,250,220,290) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '9';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        // 数字0按钮 | Number 0 button
        if (mouse_press(110,320,150,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '0';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        
        if (mouse_press(40,320,80,360) == 1) {
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++] = '#';
            ph_num[*num_len] = '\0';
            bar1(241,91,619,149,0x0085);
            x = 240 + (380 - 16 * (*num_len)) / 2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
        }
        // 删除按钮 | Delete button
        if(*num_len > 0) {
            if (mouse_press(180,320,220,360) == 1) {
                do {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                ph_num[--(*num_len)] = '\0';
                bar1(241,91,619,149,0x0085);
                x = 240 + (380 - 16 * (*num_len)) / 2;
                put_asc16_size(x,104,2,2,ph_num,0xFC44);
            }
        }
    }
    else { // 如果号码长度达到限制 | If number length reaches limit
        bar1(241,91,619,149,0x0085);
        prt_hz24_asc32(322,104,"号码应为11位!",0xFC44,"HZK\\Hzk24f");
        while(mouse.key & 1)
            MouseGet(&mouse);
        *num_len = 0;
        ph_num[0] = '\0';
    }
}