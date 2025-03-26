#include"car.h"

#ifndef __DRIVE_H__
#define __DRIVE_H__

void drive(CarStatus *state,int *puge);
void draw_drive_page();
int needle_s(CarStatus *state,double s);
int needle_n(CarStatus *state,double s);
int n_change(CarStatus *state);
#endif