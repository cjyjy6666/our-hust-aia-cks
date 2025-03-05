#ifndef __AC_H__
#define __AC_H__


#ifndef CAR_AC_H__
#define CAR_AC_H__
struct car_ac 
{
    int ac_state;
    int heating;
    int fresh_air;
    int defog;
    int temp_h;//h means higher
    int temp_l;//l means lower
    int speed_h;
    int speed_l;
    int current_temp;
    int speed;
};

#endif
void ac(int *puge);
void draw_ac_page();




#endif