// 音响控制模块 | Sound control module
// 注意：sounder不是雷声，因为sound是dos.h的关键字 | Note: sounder not thunder sound, because 'sound' is a keyword in dos.h

#include"allfunc.h"

// 音响控制主函数 | Main function for sound control
void sounder(CarStatus *state, int *puge)
{
    int volume = 50; // 初始音量 | Initial volume
    int sliderY = (int)(110+160*(100-volume)/100); // 滑块初始Y位置 | Slider initial Y position
    const int sliderX = 90; // 滑块X位置固定 | Fixed slider X position
    int newY; // 新滑块位置 | New slider position
    char vol_str[5]; // 音量显示字符串 | Volume display string
    
    mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
    sound_page(); // 绘制音响页面 | Draw sound page
    bar1(sliderX,sliderY,sliderX+20,sliderY+20,0xFFFFFF); // 绘制滑块 | Draw slider
    sprintf(vol_str,"%d%",volume); // 格式化音量字符串 | Format volume string
    put_asc16_size(80,350,2,2,vol_str,0xFFFFFF); // 显示音量 | Display volume
    mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor

    while(1) // 主循环 | Main loop
    {
        show_all(state); // 显示所有状态 | Display all status
        mouse_show(&mouse); // 显示鼠标 | Show mouse cursor
        
        button5(603,600,633,630,&state->button_s.xxx); // 返回按钮 | Back button

        // 返回按钮检测 | Back button detection
        if (mouse_press(603,600,633,630) == 1) {
            state->media_s.initialized = 0; // 重置初始化状态 | Reset initialized state
            state->media_s.first_time = 1; // 重置首次运行标志 | Reset first time flag
            *puge = 8; // 返回媒体页面 | Return to media page
            break;
        }
        
        // 音量滑块控制 | Volume slider control
        if(mouse_press(80,100,120,300) == 1) {
            newY = mouse.y - 10; // 计算新滑块位置 | Calculate new slider position
            
            // 限制滑块范围 | Limit slider range
            if(newY < 110) newY = 110;
            if(newY > 270) newY = 270;
            
            if(newY != sliderY) {
                mouse_off(&mouse); // 关闭鼠标显示 | Hide mouse cursor
                bar1(sliderX,sliderY,sliderX+20,sliderY+20,0x0085); // 清除旧滑块 | Clear old slider
                sliderY = newY; // 更新滑块位置 | Update slider position
                bar1(sliderX,sliderY,sliderX+20,sliderY+20,0xFFFFFF); // 绘制新滑块 | Draw new slider
                mouse_on(mouse); // 开启鼠标显示 | Show mouse cursor
                
                // 更新音量显示 | Update volume display
                volume = (int)(100 - 100*(sliderY-110)/160); // 计算新音量 | Calculate new volume
                bar1(80,350,160,382,0x0085); // 清除旧音量显示 | Clear old volume display
                sprintf(vol_str,"%d%",volume); // 格式化新音量字符串 | Format new volume string
                put_asc16_size(80,350,2,2,vol_str,0xFFFFFF); // 显示新音量 | Display new volume
            }
        }
        
        show_sound(state, volume); // 显示音效动画 | Show sound animation
    }
}

// 绘制音响页面 | Draw sound page
void sound_page()
{
    // 绘制返回按钮 | Draw back button
    Line2(603,600,633,600,0xFFFFFF);
    Line2(603,600,603,630,0xFFFFFF);
    Line2(603,600,633,630,0xFFFFFF);
    Line2(633,600,603,630,0xFFFFFF);
    
    // 绘制音量滑块轨道 | Draw volume slider track
    bar2(80,100,120,300,0xFFFFFF); // 外框 | Outer frame
    bar1(81,101,119,299,0x0085); // 内框 | Inner frame
    
    // 绘制音量加减符号 | Draw volume +/- symbols
    Put_Asc16_Size(90,60,2,2,'+',0xFFFFFF); // 加号 | Plus sign
    Put_Asc16_Size(90,308,2,2,'-',0xFFFFFF); // 减号 | Minus sign
    
    // 绘制"音量"文字 | Draw "Volume" text
    puthz(30,140,"音",32,32,0xFFFFFF); // 音 | Sound
    puthz(30,210,"量",32,32,0xFFFFFF); // 量 | Volume
    
    // 绘制音量数值显示框 | Draw volume value display box
    bar1(80,350,160,382,0x0085);
    
    // 绘制音效显示区 | Draw sound effect display area
    bar1(180,100,550,350,0x0085);
}

// 数值范围限制函数 | Value range limiting function
int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// 移动音效条函数 | Move sound bar function
// 参数说明 | Parameters:
// *py - 当前Y坐标指针 | Current Y coordinate pointer
// target - 目标Y坐标 | Target Y coordinate
// x - 条形的X坐标 | Bar X coordinate
// i - 条形索引 | Bar index
// color - 条形颜色 | Bar color
// 返回值: 1表示移动完成, 0表示未完成 | Return: 1 if move completed, 0 otherwise
int move_bar(CarStatus *state, int *py, int target, int x, int i, int color)
{
    if(*py > target) { // 向上移动 | Move up
        if(check_timer_expire(&(state->timer.sounder_time[i]), CLOCKS_PER_SEC/200)) {
            int delta = (*py - target) / 5; // 计算移动步长 | Calculate move step
            if(delta <= 0) delta = 1; // 最小步长为1 | Minimum step is 1
            bar1(x,*py-delta,x+40,*py,color); // 绘制移动后的条形 | Draw moved bar
            *py -= delta; // 更新位置 | Update position
            if(*py <= target) {
                *py = target; // 到达目标位置 | Reach target position
                return 1;
            }
        }
    }
    else if(*py < target) { // 向下移动 | Move down
        if(check_timer_expire(&(state->timer.sounder_time[i]), CLOCKS_PER_SEC/200)) {
            int delta = (target - *py) / 5;
            if(delta <= 0) delta = 1;
            bar1(x,*py,x+40,*py+delta,0x0085); // 清除旧条形 | Clear old bar
            *py += delta;
            if(*py >= target) {
                *py = target;
                return 1;
            }
        }
    }
    else { // 已经到达目标位置 | Already at target position
        return 1;
    }
    return 0;
}

// 显示音效动画 | Show sound animation
void show_sound(CarStatus *state, int volume)
{
    int color; // 条形颜色 | Bar color
    // 静态变量保存动画状态 | Static variables for animation state
    static int peak[9] = {0};      // 波峰位置 | Peak position
    static int valley[9] = {0};    // 波谷位置 | Valley position
    static int balance = 0;        // 基础平衡位置 | Base balance position
    static int b[9] = {0};         // 平衡偏移量 | Balance offset
    static int b_signal[9] = {0};  // 偏移方向 | Offset direction
    static int balance_p[9] = {0}; // 目标平衡位置 | Target balance position
    static int amplitude[9] = {0}; // 振幅 | Amplitude
    static int cycle[9] = {0};     // 当前周期阶段 | Current cycle phase
    static int current_y[9] = {0}; // 当前Y坐标 | Current Y coordinate

    int i;
    
    // 初始化阶段 | Initialization phase
    if(!state->media_s.initialized) {
        balance = (int)(340 - 2.3 * volume); // 根据音量计算平衡位置 | Calculate balance based on volume
        
        // 初始化每个条形 | Initialize each bar
        for(i = 0; i < 9; i++) {
            // 交替使用两种颜色 | Alternate between two colors
            color = (i%2 == 0) ? 0x7FFF : 0x0B5F;
            bar1(185 + i*40, balance, 225+i*40, 340, color); // 绘制初始条形 | Draw initial bar
            
            // 随机生成动画参数 | Generate random animation parameters
            b_signal[i] = random(2); // 随机方向 | Random direction
            b[i] = random((int)(0.1 * balance) + 1); // 随机偏移量 | Random offset
            if(b_signal[i]) b[i] = -b[i]; // 应用方向 | Apply direction
            balance_p[i] = clamp(balance + b[i], 110, 340); // 计算目标平衡位置 | Calculate target balance
            amplitude[i] = random((int)(0.5*(340-balance_p[i])) + 1); // 随机振幅 | Random amplitude
            peak[i] = clamp(balance_p[i] - amplitude[i], 110, 340); // 计算波峰 | Calculate peak
            valley[i] = clamp(balance_p[i] + amplitude[i], 110, 340); // 计算波谷 | Calculate valley
            current_y[i] = balance_p[i]; // 设置初始位置 | Set initial position
            cycle[i] = 0; // 初始周期阶段 | Initial cycle phase
        }
        state->media_s.initialized = 1; // 标记已初始化 | Mark as initialized
    }
    
    // 处理每个条形的动画 | Process animation for each bar
    for(i = 0; i < 9; i++) {
        color = (i%2 == 0) ? 0x7FFF : 0x0B5F; // 设置条形颜色 | Set bar color
        
        switch(cycle[i]) {
            case 0: // 移动到波峰 | Move to peak
                if(move_bar(state, &current_y[i], peak[i], 185 + i*40, i, color)) {
                    cycle[i] = 1; // 进入下一阶段 | Enter next phase
                }
                break;
                
            case 1: // 移动到波谷 | Move to valley
                if(move_bar(state, &current_y[i], valley[i], 185 + i*40, i, color)) {
                    cycle[i] = 2; // 进入下一阶段 | Enter next phase
                }
                break;
                
            case 2: // 返回平衡位置 | Return to balance position
                if(!state->media_s.first_time) {
                    // 重新计算参数 | Recalculate parameters
                    balance = (int)(340 - 2.3 * volume); // 更新基础平衡位置 | Update base balance
                    b_signal[i] = random(2); // 新随机方向 | New random direction
                    b[i] = random((int)(0.1 * balance) + 1); // 新随机偏移量 | New random offset
                    if(b_signal[i]) b[i] = -b[i]; // 应用方向 | Apply direction
                    balance_p[i] = clamp(balance + b[i], 110, 340); // 新目标平衡位置 | New target balance
                }
                
                // 移动到新平衡位置 | Move to new balance position
                if(move_bar(state, &current_y[i], balance_p[i], 185 + i*40, i, color)) {
                    // 计算新振幅和波峰波谷 | Calculate new amplitude, peak and valley
                    amplitude[i] = random((int)(0.5*(340-balance_p[i])) + 1);
                    peak[i] = clamp(balance_p[i]-amplitude[i], 110, 340);
                    valley[i] = clamp(balance_p[i] + amplitude[i], 110, 340);
                    cycle[i] = 0; // 重置周期 | Reset cycle
                    state->media_s.first_time = 0; // 清除首次运行标志 | Clear first time flag
                }
                break;
        }
    }
}