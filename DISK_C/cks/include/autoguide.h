#include"car.h"

#ifndef __AUTOGUIDE_H__
#define __AUTOGUIDE_H__
#define X 999
#define Max 7
#define Nopath -1


typedef struct node 
{
	int path;//上一站顶点 
	int visited;//有没有读取完成 
	int distance;//距离 
	char name;
}Node;
typedef Node* TABLE;
typedef struct {
    int x1;
	int y1;
	int x2;
	int y2; // 鼠标点击区域
    int map[Max][Max];    // 对应的地图
    int start;          // 起始点
} ClickRegion;
typedef struct PriorityQueue 
{
	int size;//当前优先队列里顶点数 
	int capacity;//队列容量 
	TABLE element[Max];
}Queue;
typedef Queue * QUEUE;

void autoguide(CarStatus *state,int *puge);
void draw_autoguide();
QUEUE InitializeQueue(int capacity);
void enqueue(QUEUE Q, TABLE K);
int dequeue(QUEUE Q);
void Dijkstra(int map[Max][Max],int start,TABLE T[]);
int getRegionX(int region);
int getRegionY(int region);
void delayer(int ms);



#endif