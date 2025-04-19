#include"car.h"

#ifndef CONTACT_H
#define CONTACT_H
void contact(CarStatus *state,int *puge);
void draw_contact_page(CarStatus *state);
int count_lines();
void read_contact(char num[7][13],int pos);
void display_contact(char num[7][13],int select);
void del_num(char num[7][13],int select);
#endif