#include"car.h"

#ifndef _SOUNDER_H_
#define _SOUNDER_H_

void sounder(CarStatus *state,int *puge);
void sound_page();
int clamp(int value,int min,int max);
int move_bar(CarStatus *state,int *py,int target,int x,int i,int color);
void show_sound(CarStatus *state,int volume);

#endif