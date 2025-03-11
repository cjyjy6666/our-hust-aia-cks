#include"allfunc.h"

void ac(CarStatus *state,int *puge)
{
    //CarStatus *status = get_car_status();
	uint8_t new_state;
	mouse_off(&mouse);
    draw_ac_page();
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
        if(mouse_press(100,90,200,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 1)
                state->ac_s.ac_state = 0;
            else
            state->ac_s.ac_state = 1;
        }
        if(mouse_press(100,190,200,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 2)
                state->ac_s.ac_state = 0;
            else
            state->ac_s.ac_state = 2;
        }
        if(mouse_press(100,290,200,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            if(state->ac_s.ac_state == 3)
                state->ac_s.ac_state = 0;
            else
                state->ac_s.ac_state = 3;
        }
        if(mouse_press(433,90,533,160) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.circulate ^= 1;
        }
        if(mouse_press(433,190,533,260) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.fresh_air ^= 1;
        }
        if(mouse_press(433,290,533,360) == 1)
        {
            do
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            }while ((mouse.key & 1) == 1);
            state->ac_s.defog ^= 1;
        }
    }
}

void draw_ac_page()
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);//閫�鍑烘寜閽?
    
    bar2(100,90,200,160,0xFFFFFF);
	bar2(100,190,200,260,0xFFFFFF);
    bar2(100,290,200,360,0xFFFFFF);
    bar2(433,90,533,160,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
    bar2(433,290,533,360,0xFFFFFF);

    puthz(130, 115, "自动",24,30,0xFFFFFF);//auto
    puthz(130, 215, "制冷",24,30,0xFFFFFF);//cold
    puthz(130, 315, "暖风",24,30,0xFFFFFF);//heating
    puthz(463, 115, "循环",24,30,0xFFFFFF);//circulation
    puthz(463, 215, "通风",24,30,0xFFFFFF); //air_refreshing
    puthz(463, 315, "除雾",24,30,0xFFFFFF);//defoging
}