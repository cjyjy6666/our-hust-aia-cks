#include"car.h"

#ifndef MUSIC_H
#define MUSIC_H
void music(CarStatus *state,int *puge);
void draw_music_page(CarStatus *state);
int count_music();
void read_music(char mus[7][15],int pos);
void display_music(char mus[7][15],int select);
#endif