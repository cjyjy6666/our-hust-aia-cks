#include"allfunc.h"


void autoguide(CarStatus *state,int *puge)
{

	ClickRegion regions[Max];ClickRegion endRegions[Max];
	int end,begin,start=0;
	int i1=0;
    TABLE T[Max];
    int map[Max][Max]={0};
	
	 int numRegions ;
	 int numEndRegions ;
	 int i,j,k;
	  // ³õÊ¼»¯ TABLE Êý×é²¢¼ì²éÄÚ´æ·ÖÅäÊÇ·ñ³É¹¦
	  for (i = 0; i < Max; i++) {
        T[i] = malloc(sizeof(Node));
        if (T[i] == NULL) {
            // ´¦ÀíÄÚ´æ·ÖÅäÊ§°ÜµÄÇé¿ö
            // ¿ÉÒÔÌí¼ÓÈÕÖ¾¼ÇÂ¼»òÆäËû´íÎó´¦ÀíÂß¼­
            return;
        }
	}




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
        if((mouse_press(340, 20, 480, 80) == 1)&&(i1==0))
		{
			initializeClickRegions(regions);

			i1=1;
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            // put_asc16_number_size(750,100,2,2,regions[6].start,0x000000);
		

			mouse_off(&mouse);
			bar1(340, 20, 480, 80,0x340F);
			puthz(352,25,"Æðµã",48,55,0x000000);
			puthz(531,89,"ÇëÔÚ×ó²àÍ¼ÖÐÑ¡ÔñÆðµã",48,45,0x19E6);

			mouse_on(mouse);


			
			numRegions = sizeof(regions) / sizeof(regions[0]);
		}
	
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â¼ï¿?
		for (i = 0; i < numRegions; i++) {
			if ((mouse_press(regions[i].x1, regions[i].y1, regions[i].x2, regions[i].y2) == 1)&&(i1==1)) {
				TABLE temp;
				do {
					MouseGet(&mouse);
					mouse_show(&mouse);
					} while ((mouse.key & 1) == 1);
					
				memcpy(map, regions[i].map, sizeof(map));
				mouse_off(&mouse);
				bar1(340, 95, 480, 155,0xFF44);
		        puthz(352,100,"ÖÕµã",48,55,0x000000);
				Circlefill((regions[i].x1)+20,(regions[i].y1)+20,3,0xF800);
				bar1(515,82,1000,148,0x7FFE);
				mouse_on(mouse);
				Dijkstra(map,0, T);
				for(j=0;j<Max;j++){
					switch(regions[i].start){
					case 0:break;
					case 1:if(T[j]->path==0)T[j]->path+=1;break;
					case 2:if(T[j]->path==0)T[j]->path+=2;break;
					case 3:if(T[j]->path==0)T[j]->path+=3;break;
					case 4:if(T[j]->path==0)T[j]->path+=4;break;
					case 5:if(T[j]->path==0)T[j]->path+=5;break;
					case 6:if(T[j]->path==0)T[j]->path+=6;break;
					}
				}
				switch(regions[i].start){
					case 0:break;
					case 1:temp=T[0];T[0]=T[1];T[1]=temp;break;
					case 2:temp=T[0];T[0]=T[2];T[2]=temp;break;
					case 3:temp=T[0];T[0]=T[3];T[3]=temp;break;
					case 4:temp=T[0];T[0]=T[4];T[4]=temp;break;
					case 5:temp=T[0];T[0]=T[5];T[5]=temp;break;
					case 6:temp=T[0];T[0]=T[6];T[6]=temp;break;
					}
					
				begin=regions[i].start;
                // put_asc16_number_size(750,100,2,2,begin,0x000000);
				i1=2;
				break;
			}
			else if(mouse_press(340, 170, 480, 230) == 1&&(i1==1)) {
				i1=0;
				
				mouse_off(&mouse);

				draw_autoguide();
			
				mouse_on(mouse);
				break;
			}			
		}
			
	
			// ï¿½ï¿½ï¿½ï¿½ï¿½Õµï¿½Ñ¡ï¿½ï¿½
		if((mouse_press(340, 95, 480, 155) == 1)&&(i1==2))
		{
			initializeClickRegions(endRegions);

			i1=3;
            // put_asc16_number_size(750,100,2,2,endRegions[6].start,0x000000);


			do {
				MouseGet(&mouse);
				mouse_show(&mouse);
			} while ((mouse.key & 1) == 1);

			mouse_off(&mouse);
			bar1(340, 95, 480, 155,0x340F);
			puthz(352,100,"ÖÕµã",48,55,0x000000);
			puthz(531,89,"ÇëÔÚ×ó²àÍ¼ÖÐÑ¡ÔñÖÕµã",48,45,0x19E6);

			mouse_on(mouse);

				
			numEndRegions = sizeof(endRegions) / sizeof(endRegions[0]);
		}
		else if((mouse_press(340, 170, 480, 230) == 1)&&(i1==2))
			{
				i1=0;
				
			    mouse_off(&mouse);

				draw_autoguide();
			 
				mouse_on(mouse);
            
			}			 
	
		for (i = 0; i < numEndRegions; i++) {
			if ((mouse_press(endRegions[i].x1, endRegions[i].y1, endRegions[i].x2, endRegions[i].y2) == 1)&&(i1==3)) {
				i1=4;
                do {
				MouseGet(&mouse);
				mouse_show(&mouse);
				} while ((mouse.key & 1) == 1);
						
				end = endRegions[i].start;
                // put_asc16_number_size(750,100,2,2,end,0x000000);
				mouse_off(&mouse);
				bar1(340, 170, 480, 230,0xFF44);
		        puthz(352,175,"¿ªÊ¼",48,55,0x000000);				
				bar1(515,82,1000,148,0x7FFE);
				Circlefill((endRegions[i].x1)+20,(endRegions[i].y1)+20,3,0xF800);
				mouse_on(mouse);

				break;
			}
			

		}

		if((mouse_press(340, 170, 480, 230) == 1)&&(i1==4))
		{
			 // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â·ï¿½ï¿?
			 int time;
			 int path[Max];
			 int pathLength = 0;
			 int current = end;
			 while (current != begin) {
				 path[pathLength] = current;
				 pathLength++;
				 current = T[current]->path;
			 }
			 path[pathLength] = begin;
			 pathLength++;
		 
			 // ï¿½ï¿½×ªÂ·ï¿½ï¿½ï¿½ï¿½Ê¹ï¿½ï¿½ï¿½ï¿½ï¿½ãµ½ï¿½Õµï¿½
			 for (j= 0; j < pathLength / 2; j++) {
				 int temp = path[j];
				 path[j] = path[pathLength - j - 1];
				 path[pathLength - j - 1] = temp;
			 }
			 time=T[end]->distance;
			 i1=5;
			
		 
			 // ï¿½ï¿½ï¿½ï¿½Ð¡ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			 for (j= 0; j < pathLength - 1; j++) {
				int x1;int y1;int x2;int y2;
				  x1 = getRegionX(path[j]);
				  y1 = getRegionY(path[j]);
				  x2 = getRegionX(path[j + 1]);
				  y2 = getRegionY(path[j + 1]);
				 Line_Thick(x1, y1, x2, y2, 1, 0xF800);
			 }
			for (j= 0; j < pathLength - 1; j++) {
				int x1;int y1;int x2;int y2; int stepX;int stepY;
				x1 = getRegionXx(path[j]);
				y1 = getRegionYy(path[j]);
				x2 = getRegionXx(path[j + 1]);
				y2 = getRegionYy(path[j + 1]);
				stepX = (int)((x2 - x1) / 10);
				stepY = (int)((y2 - y1) / 10);
				for (k = 0; k <= 10; k++) {
					int x = x1 + stepX * k;
					int y = y1 + stepY * k;
					Circlefill(x, y,8, 0xF800);
					delayer(10);

				}
			 }
			mouse_off(&mouse);
			puthz(531,89,"±¾´Îµ¼º½ÓÃÊ±    ·ÖÖÓ",48,45,0x19E6);
			bar1(801, 84, 890, 141,0x7FFE);
			put_asc16_number_size(820, 93,3,3,time,0xFFA5);
			bar1(340, 170, 480, 230,0xFF44);
		    puthz(352,175,"Íê³É",48,55,0x000000);
			mouse_on(mouse);

		 
			 
		}
		if((mouse_press(340, 170, 480, 230) == 1)&&(i1==5)){
			i1=0;
			mouse_off(&mouse);

			draw_autoguide();

			mouse_on(mouse);
		}

	
			
		

		
		
	}
    for (i = 0; i < Max; i++) {
        free(T[i]);
    }
}

void initializeClickRegions(ClickRegion regions[Max]) {
    ClickRegion a = {21, 26, 55, 55, {
        //a,b,c,d,e,f,g
        {0, 5, 4, X, X, X, X}, //a
        {5, 0, 3, X, 5, X, X}, //b
        {4, 3, 0, 6, 5, X, X}, //c
        {X, X, 6, 0, 5, 5, X}, //d
        {X, 5, 5, 5, 0, 7, 5}, //e
        {X, X, X, 5, 7, 0, 5}, //f
        {X, X, X, X, 5, 5, 0}  //g
    }, 0};
    ClickRegion b = {23, 159, 59, 205, {
        //b,a,c,d,e,f,g
        {0, 5, 3, X, 5, X, X}, //b
        {5, 0, 4, X, X, X, X}, //a
        {3, 4, 0, 6, 5, X, X}, //c
        {X, X, 6, 0, 5, 5, X}, //d
        {5, X, 5, 5, 0, 7, 5}, //e
        {X, X, X, 5, 7, 0, 5}, //f
        {X, X, X, X, 5, 5, 0}  //g
    }, 1};
    ClickRegion c = {71, 110, 107, 145, {
        //c,b,a,d,e,f,g
        {0, 3, 4, 6, 5, X, X}, //c
        {3, 0, 5, X, 5, X, X}, //b
        {4, 5, 0, X, X, X, X}, //a
        {6, X, X, 0, 5, 5, X}, //d
        {5, 5, X, 5, 0, 7, 5}, //e
        {X, X, X, 5, 7, 0, 5}, //f
        {X, X, X, X, 5, 5, 0}  //g
    }, 2};
    ClickRegion d = {134, 41, 187, 78, {
        //d,b,c,a,e,f,g
        {0, X, 6, X, 5, 5, X}, //d
        {X, 0, 3, 5, 5, X, X}, //b
        {6, 3, 0, 4, 5, X, X}, //c
        {X, 5, 4, 0, X, X, X}, //a
        {5, 5, 5, X, 0, 7, 5}, //e
        {5, X, X, X, 7, 0, 5}, //f
        {X, X, X, X, 5, 5, 0}  //g
    }, 3};
    ClickRegion e = {140, 158, 186, 198, {
        //e,b,c,d,a,f,g
        {0, 5, 5, 5, X, 7, 5}, //e
        {5, 0, 3, X, 5, X, X}, //b
        {5, 3, 0, 6, 4, X, X}, //c
        {5, X, 6, 0, X, 5, X}, //d
        {X, 5, 4, X, 0, X, X}, //a
        {7, X, X, 5, X, 0, 5}, //f
        {5, X, X, X, X, 5, 0}  //g
    }, 4};
    ClickRegion f = {251, 34, 294, 78, {
        //f,b,c,d,e,a,g
        {0, X, X, 5, 7, X, 5}, //f
        {X, 0, 3, X, 5, 5, X}, //b
        {X, 3, 0, 6, 5, 4, X}, //c
        {5, X, 6, 0, 5, X, X}, //d
        {7, 5, 5, 5, 0, X, 5}, //e
        {X, 5, 4, X, X, 0, X}, //a
        {5, X, X, X, 5, X, 0}  //g
    }, 5};
    ClickRegion g = {254, 158, 294, 199, {
        //g,b,c,d,e,f,a
        {0, X, X, X, 5, 5, X}, //g
        {X, 0, 3, X, 5, X, 5}, //b
        {X, 3, 0, 6, 5, X, 4}, //c
        {X, X, 6, 0, 5, 5, X}, //d
        {5, 5, 5, 5, 0, 7, X}, //e
        {5, X, X, 5, 7, 0, X}, //f
        {X, 5, 4, X, X, X, 0}  //a
    }, 6};

    regions[0] = a;
    regions[1] = b;
    regions[2] = c;
    regions[3] = d;
    regions[4] = e;
    regions[5] = f;
    regions[6] = g;
}

// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È¡ï¿½ï¿½ï¿½ï¿½ï¿½Xï¿½ï¿½ï¿½ï¿½
int getRegionX(int region) {
	

    switch (region) {
        case 0: return 39;
        case 1: return 39;
        case 2: return 88;
        case 3: return 160;
        case 4: return 160;
        case 5: return 272;
        case 6: return 272;
        default: return 0;
    }
}

int getRegionXx(int region) {
	

    switch (region) {
        case 0: return 111;
        case 1: return 111;
        case 2: return 277;
        case 3: return 517;
        case 4: return 517;
        case 5: return 891;
        case 6: return 891;
        default: return 0;
    }
}
// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È¡ï¿½ï¿½ï¿½ï¿½ï¿½Yï¿½ï¿½ï¿½ï¿½
int getRegionY(int region) {
	
    switch (region) {
        case 0: return 42;
        case 1: return 183;
        case 2: return 130;
        case 3: return 59;
        case 4: return 183;
        case 5: return 59;
        case 6: return 183;
        default: return 0;
    }
}
int getRegionYy(int region) {
	
    switch (region) {
        case 0: return 326;
        case 1: return 692;
        case 2: return 552;
        case 3: return 377;
        case 4: return 692;
        case 5: return 377;
        case 6: return 692;
        default: return 0;
    }
}
// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ó³Ùºï¿½ï¿½ï¿½
void delayer(int ms) {
    long endTime = clock() + ms;
    while (clock() < endTime);
}

void draw_autoguide()
{
    bar1(0, 0, 1024, 768,0x7FFE);
	bar1(0,0,320,250,0x025C);
   
    Line_Thick(0,250,1024,250, 1,0x000000);
	Line_Thick(320,0,320,250,1, 0x000000);
	
	Line_Thick(111,326,111,692,1, 0x000000);
	Line_Thick(111,326,277,551,1, 0x000000);
	Line_Thick(277,551,111,692,1, 0x000000);
	Line_Thick(277,551,517,692,1, 0x000000);
	Line_Thick(111,692,517,692,1, 0x000000);
	Line_Thick(277,551,517,377,1, 0x000000);
	Line_Thick(517,377,517,692,1, 0x000000);
	Line_Thick(517,377,891,377,1, 0x000000);
	Line_Thick(517,692,891,692,1, 0x000000);
	Line_Thick(891,377,891,692,1, 0x000000);
	Line_Thick(517,692,891,377,1, 0x000000);
	Line_Thick(39,42,39,183,1, 0x000000);
	Line_Thick(39,42,88,130,1, 0x000000);
	Line_Thick(39,183,88,130,1, 0x000000);
	Line_Thick(88,130,160,59,1, 0x000000);
	Line_Thick(88,130,160,183,1, 0x000000);
	Line_Thick(39,183,160,183,1, 0x000000);
	Line_Thick(160,59,160,183,1, 0x000000);
	Line_Thick(160,59,272,59,1, 0x000000);
	Line_Thick(160,183,272,183,1, 0x000000);
	Line_Thick(272,59,272,183,1, 0x000000);
	Line_Thick(160,183,272,59,1, 0x000000);
	bar1(64,295,173,359, 0x7BEF);//1ï¿??
    bar2(64,295,173,359,0x000000);
	bar1(65,631,189,742, 0x7BEF);//2ï¿??
    bar2(65,631,189,742,0x000000);
	bar1(223,506,344,599, 0x7BEF);//3ï¿?? 
    bar2(223,506,344,599,0x000000);
	bar1(436,330,612,426, 0x7BEF);//4ï¿??
    bar2(436,330,612,426,0x000000);
	bar1(450,630,605,727, 0x7BEF);//5ï¿??
	bar2(450,630,605,727,0x000000);
    bar1(819,316,959,427, 0x7BEF);//6ï¿??
    bar2(819,316,959,427,0x000000);
	bar1(825,624,962,730, 0x7BEF);//7ï¿??
    bar2(825,624,962,730,0x000000);
	bar1(21,26,55,55, 0x7BEF);
    bar2(21,26,55,55,0x000000);//
    bar1(23,159,59,205, 0x7BEF);
    bar2(23,159,59,205,0x000000);//
    bar1(71,110,107,145, 0x7BEF);
    bar2(71,110,107,145,0x000000);//
    bar1(134,41,187,78, 0x7BEF);
    bar2(134,41,187,78,0x000000);//
    bar1(140,158,186,198, 0x7BEF);
    bar2(140,158,186,198,0x000000);//
    bar1(251,34,294,78, 0x7BEF);
    bar2(251,34,294,78,0x000000);//
    bar1(254,158,294,199, 0x7BEF);
    bar2(254,158,294,199,0x000000);//
    bar1(340, 20, 480, 80,0xFF44);
    bar1(340, 95, 480, 155,0x340F);
    bar1(340, 170, 480, 230,0x340F);
	puthz(70,303,"Ò»¶°",48,45,0x000000);
	puthz(73,663,"¶þ¶°",48,45,0x000000);
	puthz(231,530,"Èý¶°",48,45,0x000000);
	puthz(470,354,"ËÄ¶°",48,45,0x000000);
	puthz(474,657,"Îå¶°",48,45,0x000000);
	puthz(836,352,"Áù¶°",48,45,0x000000);
	puthz(836,657,"Æß¶°",48,45,0x000000);
	puthz(352,25,"Æðµã",48,55,0x000000);
	puthz(352,100,"ÖÕµã",48,55,0x000000);
	puthz(352,175,"È¡Ïû",48,55,0x000000);
	bar1(0,248,1024,280,0x02F8);
	bar1(0,248,46,768,0x02F8);
	bar1(0,730,1024,768,0x02F8);
	bar1(965,248,1024,768,0x02F8);
	Line_Thick(46,280,965,280,1, 0x000000);
	Line_Thick(46,280,46,730,1, 0x000000);
	Line_Thick(46,730,965,730,1, 0x000000);
	Line_Thick(965,280,965,730,1, 0x000000);
	Line_Thick(0,250,46,280,1, 0x000000);
	Line_Thick(1024,250,965,280,1, 0x000000);
	Line_Thick(0,768,46,730,1, 0x000000);
	Line_Thick(1024,768,965,730,1, 0x000000);
	Line_Thick(0,250,1024,250, 1,0x000000);
	bar1(965,0,1024,53,0xF800);
    Line_Thick(965,0,1024,53, 1,0x000000);
    Line_Thick(965,53,1024,0, 1,0x000000);




}






void InitializeTable(int start,TABLE T[])//åˆï¿½?ï¿½åŒ–è¡¨æ ¼	
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

QUEUE InitializeQueue(int capacity)//åˆï¿½?ï¿½åŒ–é˜Ÿåˆ—
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

void enqueue(QUEUE Q, TABLE K)//å…¥é˜Ÿ
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

int dequeue(QUEUE Q)//å‡ºé˜Ÿ
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


