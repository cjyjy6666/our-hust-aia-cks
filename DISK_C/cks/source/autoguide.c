#include"allfunc.h"


void autoguide(int *puge)
{

    TABLE T[Max];
    int map[Max][Max]={'0'};


    mouse_off(&mouse);

	draw_autoguide();



	mouse_on(mouse);

	while (1)
	{
		mouse_show(&mouse);
        if(mouse_press(965,0,1024,53) == 1)
        {
            *puge=2;
            break;
        }


		
		
	}
}

void draw_autoguide()
{
    bar1(0, 0, 1024, 768,0x7FFE);
    bar1(965,0,1024,53,0xF800);
    Line_Thick(965,0,1024,53, 1,0x000000);
    Line_Thick(965,53,1024,0, 1,0x000000);
    Line_Thick(0,250,1024,250, 1,0x000000);
	Line_Thick(320,0,320,250,1, 0x000000);
	bar1(64,295,173,359, 0x7BEF);//1栋
    bar2(64,295,173,359,0x000000);
	bar1(65,631,189,742, 0x7BEF);//2栋
    bar2(65,631,189,742,0x000000);
	bar1(223,506,344,599, 0x7BEF);//3栋 
    bar2(223,506,344,599,0x000000);
	bar1(436,330,612,426, 0x7BEF);//4栋
    bar2(436,330,612,426,0x000000);
	bar1(450,630,605,727, 0x7BEF);//5栋
	bar2(450,630,605,727,0x000000);
    bar1(819,316,959,427, 0x7BEF);//6栋
    bar2(819,316,959,427,0x000000);
	bar1(825,624,962,730, 0x7BEF);//7栋
    bar2(825,624,962,730,0x000000);
	bar1(21,26,55,55, 0x7BEF);
    bar2(21,26,55,55,0x000000);
    bar1(23,159,59,205, 0x7BEF);
    bar2(23,159,59,205,0x000000);
    bar1(71,110,107,145, 0x7BEF);
    bar2(71,110,107,145,0x000000);
    bar1(134,41,187,78, 0x7BEF);
    bar2(134,41,187,78,0x000000);
    bar1(140,158,186,198, 0x7BEF);
    bar2(140,158,186,198,0x000000);
    bar1(251,34,294,78, 0x7BEF);
    bar2(251,34,294,78,0x000000);
    bar1(254,158,294,199, 0x7BEF);
    bar2(254,158,294,199,0x000000);
    Line_Thick(112,359,112,631,1, 0x000000);
    Line_Thick(147,359,251,506, 1,0x000000);
    Line_Thick(189,641,233,599, 1,0x000000);
    Line_Thick(344,550,518,550, 1,0x000000);
    Line_Thick(189,693,450,693, 1,0x000000);
    Line_Thick(518,426,518,630, 1,0x000000);
    Line_Thick(612,343,819,343, 1,0x000000);
    Line_Thick(896,427,896,624, 1,0x000000);
    Line_Thick(605,692,825,692, 1,0x000000);
    Line_Thick(580,630,819,416, 1,0x000000);
    Line_Thick(37,55,37,159, 1,0x000000);
    Line_Thick(48,55,80,110, 1,0x000000);
    Line_Thick(59,161,72,145, 1,0x000000);
    Line_Thick(107,128,159,128, 1,0x000000);
    Line_Thick(159,78,159,158, 1,0x000000);
    Line_Thick(59,184,140,184, 1,0x000000);
    Line_Thick(187,48,251,48, 1,0x000000);
    Line_Thick(272,78,272,158, 1,0x000000);
    Line_Thick(186,184,254,184, 1,0x000000);
    Line_Thick(179,158,251,72, 1,0x000000);
    bar1(340, 20, 480, 60,0x340F);
    bar1(340, 90, 480, 130,0x340F);
    bar1(340, 170, 480, 230,0x340F);



}






void InitializeTable(int start,TABLE T[])//初始化表格	
{
	int i;
	for(i=0;i<Max;i++)
	{
		T[i]=malloc(sizeof(Node));
		T[i]->visited=0;
		T[i]->path=Nopath;
		T[i]->distance=X;
		T[i]->name=65+i;
	}
	T[start]->distance=0;
	
}

QUEUE InitializeQueue(int capacity)//初始化队列
{
    int i;
	QUEUE Q;
	Q=malloc(sizeof(Queue));
	Q->capacity=capacity;
	Q->size=0;
	
	for(i=1;i<Max;i++)
	{
		Q->element[i]=NULL;
	}
	Q->element[0]=malloc(sizeof(Node));
	Q->element[0]->distance=0;
	
	return Q;
	
}

void enqueue(QUEUE Q, TABLE K)//入队
{
	int i,hole;
	
	if(K->path==Nopath)
	{
		Q->size++;
		hole=Q->size;
	}
	else
	{
		i=1;
		while(K->name!=Q->element[i]->name&&Q->element[i]!=NULL)
		{
			i++;
		} 
		hole=i;	
	}
	i=hole/2;
	
	while(K->distance < Q->element[i]->distance)
	{
		Q->element[hole]=Q->element[i];
		hole=i;
		i=i/2;
	}
	Q->element[hole]=K;
}

int dequeue(QUEUE Q)//出队
{	TABLE OUT;
	int hole=1,child=2,last=Q->size;
	OUT=Q->element[1];
	Q->size--;
	while(child <= Q->size && Q->element[child]->distance < Q->element[last]->distance  )
	{	
		
		if(Q->element[child]->distance > Q->element[child+1]->distance )	
			child++;			
		Q->element[hole]=Q->element[child];
		hole=child;
		child=hole*2;	
	}
	
	Q->element[hole]=Q->element[last];
	Q->element[last]=NULL;
	
	return OUT->name-65;
	
}

void Dijkstra(int map[Max][Max],int start,TABLE T[])
{
	int i;
	int current;
    QUEUE Q;
	InitializeTable(start,T);
	Q=InitializeQueue(Max);
	enqueue(Q,T[start]);
	while(Q->size!=0)
	{
		current=dequeue(Q);
	
		for(i=0;i<Max;i++)
		{
			int EdgeLength = map[current][i];
			
			if(EdgeLength!=0 && EdgeLength!=X && T[i]->visited==0)
			{
				if(T[i]->distance > EdgeLength + T[current]->distance)
				{
					T[i]->distance = EdgeLength + T[current]->distance;
					enqueue(Q,T[i]);
					T[i]->path=current;
				}	
			}
		}
		T[current]->visited=1;
	}
}


