#include"allfunc.h"

void wiper(CarStatus *state,int *puge)
{
	mouse_off(&mouse);
    draw_wiper_page();
    mouse_on(mouse);

    while(1)
    {
        show_all(state);	
        mouse_show(&mouse);
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;
			break;
		}
        if (mouse_press(100,190,200,260) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.auto_w^= 1;
            state->wiper_s.once = 0;
            state->wiper_s.fast = 0;
            state->wiper_s.slow = 0;
        }
        if (mouse_press(100,290,200,360) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.once^= 1;
            state->wiper_s.fast = 0;
            state->wiper_s.slow = 0;
            state->wiper_s.auto_w = 0;
            state->timer.wiper_time = clock();
        }
        if (mouse_press(433,190,533,260) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.fast^= 1;
            state->wiper_s.slow = 0;
            state->wiper_s.auto_w = 0;
            state->wiper_s.once = 0;
        }
        if (mouse_press(433,290,533,360) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->wiper_s.slow^= 1;
            state->wiper_s.fast = 0;
            state->wiper_s.auto_w = 0;
            state->wiper_s.once = 0;
        }
        /* 雨刷逻辑 */
        // 自动模式优先
        if(state->wiper_s.auto_w) 
        {
            if(state->wiper_s.rain == 2) 
            {       // 大雨
                state->wiper_s.cur_wip = 2;
            } 
            else if(state->wiper_s.rain == 1) 
            { // 小雨
                state->wiper_s.cur_wip = 1;
            } 
            else 
            {                              // 晴天
                state->wiper_s.cur_wip = 0;
            }
        }
        // 手动模式（互斥）
        else if(state->wiper_s.fast) 
        {
            state->wiper_s.cur_wip = 2;
        }
        else if(state->wiper_s.slow) 
        {
            state->wiper_s.cur_wip = 1;
        }
        // 单次模式（最高优先级）
        else if(state->wiper_s.once) 
        {
            state->wiper_s.cur_wip = 1;  // 改为慢速刮
            if(check_timer_expire(&(state->timer.wiper_time), CLOCKS_PER_SEC)) 
            {
                state->wiper_s.cur_wip = 0;
                state->wiper_s.once = 0; // 重置单次模式
            }
        }
        // 默认状态
        else 
        {
            state->wiper_s.cur_wip = 0;
        }
    }
}

void draw_wiper_page()
{
    bar2(100,190,200,260,0xFFFFFF);
	bar2(100,290,200,360,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
	puthz(130, 215, "自动",24,30,0xFFFFFF);//auto
    puthz(130, 315, "手动",24,30,0xFFFFFF);//wipe once
    puthz(463, 215, "高速",24,30,0xFFFFFF); //fast
    puthz(463, 315, "低速",24,30,0xFFFFFF); //slow
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}