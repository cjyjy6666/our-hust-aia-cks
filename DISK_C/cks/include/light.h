#ifndef __LIGHT_H__
#define __LIGHT_H__

// 在头文件中，使用防止重复声明的宏
#ifndef CAR_LIGHT_H
#define CAR_LIGHT_H

struct car_light {
    int right;
    int left;
    int fog;
    int near_light;
    int far_light;
    int left_blink_state;
    int right_blink_state;
};

#endif


void light(int *puge);
void draw_light_page(void);
void show_light(struct car_light light_status);


#endif