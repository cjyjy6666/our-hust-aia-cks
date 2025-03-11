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
        
        // 锟睫革拷锟斤拷锟斤拷锟斤拷呒锟斤拷锟斤拷锟斤拷锟斤拷头偶锟斤拷锟斤拷锟�
        if (mouse_press(433,190,533,260) == 1) {
            // 锟饺达拷锟斤拷锟斤拷头锟�
            do {
                MouseGet(&mouse);      // 锟斤拷锟斤拷锟斤拷取锟斤拷锟斤拷状态
                mouse_show(&mouse);   // 锟斤拷锟斤拷锟斤拷锟斤拷锟绞撅拷锟斤拷锟�
            } while ((mouse.key & 1) == 1);  // 锟斤拷锟斤拷锟斤拷状态位
            
            state->light_s.near_light ^= 1;
        }

        if (mouse_press(433,290,533,360) == 1) {
            // 锟饺达拷锟斤拷锟斤拷头锟�
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
            
            // 锟叫伙拷双锟斤拷状态
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

/*	锟斤拷锟斤拷锟斤拷锟斤拷小锟斤拷锟斤拷
没锟斤拷写双锟斤拷锟斤拷锟斤拷锟揭ｏ拷转同时锟斤拷锟铰碉拷锟斤拷锟斤拷
双锟斤拷锟斤拷钮锟斤拷detect写锟侥的撅拷锟轿凤拷围锟斤拷锟斤拷锟皆改斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
*/

/*锟斤拷锟解，锟斤拷锟斤拷锟斤拷婊癸拷锟斤拷锟绞憋拷洌�锟斤拷锟皆硷拷锟斤拷锟皆讹拷锟斤拷锟�
*/

void draw_light_page()
{
	/*draw_botton(100,190,200,260,0x00FF,0x0000);
	draw_botton(100,290,200,360,0x00FF,0x0000);
	draw_botton(266,440,366,510,0x00FF,0x0000);
	draw_botton(433,190,533,260,0x00FF,0x0000);
	draw_botton(433,290,533,360,0x00FF,0x0000);*/
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
	puthz(130, 215, "锟斤拷转",24,30,0xFFFFFF);
    puthz(130, 315, "锟斤拷转",24,30,0xFFFFFF);
    puthz(296, 315, "锟斤拷锟斤拷",24,30,0xFFFFFF);
    puthz(463, 215, "锟斤拷锟斤拷",24,30,0xFFFFFF); 
    puthz(463, 315, "远锟斤拷",24,30,0xFFFFFF); 
	Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);
}


