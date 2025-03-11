#include"allfunc.h"



void light(CarStatus* state,int *puge)
{
	//CarStatus *status = get_car_status();
	uint8_t new_state;
	mouse_off(&mouse);

	draw_light_page();



	mouse_on(mouse);


	while(1)
	{
		show_all(state);
		
		mouse_show(&mouse);
        

        if (mouse_press(433,190,533,260) == 1) {
            
            do {
                MouseGet(&mouse); 
                mouse_show(&mouse); 
            } while ((mouse.key & 1) == 1);  
            
            state->light_s.near_light ^= 1;
        }

        if (mouse_press(433,290,533,360) == 1) 
		{
            do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->light_s.far_light ^= 1;    
        }

		if (mouse_press(100,190,200,260) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
			if(state->light_s.left) {
                state->light_s.left = 0;
                state->light_s.left_blink_state = 0;
    
            }

            state->light_s.right^=1;
			state->light_s.right_blink_state=state->light_s.right;
			
		}
		if (mouse_press(100,290,200,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
			if(state->light_s.right) {
                state->light_s.right = 0;
                state->light_s.right_blink_state = 0;
                
            }
			
            state->light_s.left^=1;
			state->light_s.left_blink_state=state->light_s.left;
			
		}
		if (mouse_press(266,290,366,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            
            state->light_s.fog ^= 1;
		}
		if (mouse_press(266,63,366,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            

            new_state = !(state->light_s.right && state->light_s.left);
            state->light_s.right = new_state;
            state->light_s.left = new_state;
            state->light_s.right_blink_state = new_state;
            state->light_s.left_blink_state = new_state;
            
            
		}
		if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 2;
			break;
		}
	}

}


void draw_light_page()
{

	bar2(100,190,200,260,0xFFFFFF);
	bar2(100,290,200,360,0xFFFFFF);
	bar2(266,290,366,360,0xFFFFFF);
	bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
	Line2(316,63,266,150,0xF800);
	Line2(316,63,366,150,0xF800);
	Line2(266,150,366,150,0xF800);
	Line2(316,73,275,145,0xF800);
	Line2(316,73,357,145,0xF800);
	Line2(275,145,357,145,0xF800);
	Put_Asc16_Size(308, 100, 2, 2, '!', 0xF800);
	puthz(130, 215, "右转",24,30,0xFFFFFF);//turn right
    puthz(130, 315, "左转",24,30,0xFFFFFF);//turn left
    puthz(296, 315, "雾灯",24,30,0xFFFFFF);//fog light
    puthz(463, 215, "近光",24,30,0xFFFFFF); //near light
    puthz(463, 315, "远光",24,30,0xFFFFFF); //far light
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}


