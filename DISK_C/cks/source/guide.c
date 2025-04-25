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
	  // 初始化 TABLE 数组并检查内存分配是否成功
	  for (i = 0; i < Max; i++) {
        T[i] = malloc(sizeof(Node));
        if (T[i] == NULL) {
            // 处理内存分配失败的情况
            // 可以添加日志记录或其他错误处理逻辑
            return;
        }
	}




    mouse_off(&mouse);

	draw_autoguide();

	mouse_on(mouse);

	while (1)
	{
		

		mouse_show(&mouse);

         if (mouse.x >= 340 && mouse.x <= 480 && mouse.y >= 20 && mouse.y <= 80 && !state->button_s.qidian&&(i1==0)) {
            state->button_s.qidian=1;
            mouse_off(&mouse);
            bar1(340, 20, 480, 80,0xFD44);
            puthz(352,25,"起点",48,55,0x000000);
            mouse_on(mouse);
        } else if (state->button_s.qidian&&(i1==0) && (mouse.x < 340 || mouse.x > 480 || mouse.y < 20 || mouse.y > 80)) {
            state->button_s.qidian = 0;
            mouse_off(&mouse);
            bar1(340, 20, 480, 80,0xFF44);
            puthz(352,25,"起点",48,55,0x000000);
            mouse_on(mouse);
        }

      
	
			// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷录锟?
         if (mouse.x >= 340 && mouse.x <= 480 && mouse.y >= 95 && mouse.y <= 155 && (!state->button_s.zhongdian)&&(i1==2)) {
            state->button_s.zhongdian=1;
            mouse_off(&mouse);
            bar1(340, 95, 480, 155, 0xFD44);
            puthz(352,100,"终点",48,55,0x000000);
            mouse_on(mouse);
        } else if (state->button_s.zhongdian&&(i1==2) && (mouse.x < 340 || mouse.x > 480 || mouse.y < 95 || mouse.y > 155)) {
            state->button_s.zhongdian = 0;
            mouse_off(&mouse);
            bar1(340, 95, 480, 155, 0xFF44);
            puthz(352,100,"终点",48,55,0x000000);
            mouse_on(mouse);
        }

        
        if (mouse.x >= 340 && mouse.x <= 480 && mouse.y >= 170 && mouse.y <= 230 && !state->button_s.kaishi&&(i1==4)) {
            state->button_s.kaishi=1;
            mouse_off(&mouse);
			bar1(340, 170, 480, 230,0xFD44);
			puthz(352,175,"开始",48,55,0x000000);				
            mouse_on(mouse);
        } else if (state->button_s.kaishi&&(i1==4) && (mouse.x < 340 || mouse.x > 480 || mouse.y < 170 || mouse.y > 230)) {
            state->button_s.kaishi = 0;
            mouse_off(&mouse);
			bar1(340, 170, 480, 230,0xFF44);
			puthz(352,175,"开始",48,55,0x000000);				
            mouse_on(mouse);
        }

        if (mouse.x >= 340 && mouse.x <= 480 && mouse.y >= 170 && mouse.y <= 230 && !state->button_s.wancheng&&(i1==5)) {
            state->button_s.wancheng=1;
            mouse_off(&mouse);
			bar1(340, 170, 480, 230,0xFD44);
            puthz(352,175,"完成",48,55,0x000000);
            mouse_on(mouse);
        } else if (state->button_s.wancheng&&(i1==5) && (mouse.x < 340 || mouse.x > 480 || mouse.y < 170 || mouse.y > 230)) {
            state->button_s.wancheng = 0;
            mouse_off(&mouse);
			bar1(340, 170, 480, 230,0xFF44);
            puthz(352,175,"完成",48,55,0x000000);
            mouse_on(mouse);
        }

        if (mouse.x >= 340 && mouse.x <= 480 && mouse.y >= 170 && mouse.y <= 230 && !state->button_s.quxiao&&(i1==1||i1==2||i1==3)) {
            state->button_s.quxiao=1;
            mouse_off(&mouse);
            bar1(340, 170, 480, 230,0x320F);
            puthz(352,175,"取消",48,55,0x000000);
            mouse_on(mouse);
        } else if (state->button_s.quxiao&&(i1==1||i1==2||i1==3) && (mouse.x < 340 || mouse.x > 480 || mouse.y < 170 || mouse.y > 230)) {
            state->button_s.quxiao = 0;
            mouse_off(&mouse);
            bar1(340, 170, 480, 230,0x340F);
            puthz(352,175,"取消",48,55,0x000000);
            mouse_on(mouse);
        }

        if (mouse.x >= 440 && mouse.x <= 580 && mouse.y >= 400 && mouse.y <= 460 && !state->button_s.queding&&(i1==6)) {
            state->button_s.queding=1;
            mouse_off(&mouse);
            bar1(440, 400, 580, 460, 0x8410); 
            bar2(440, 400, 580, 460, 0x000000);
            puthz(452, 405, "确定", 48,55, 0x000000);
            mouse_on(mouse);
        } else if (state->button_s.queding&&(i1==6) && (mouse.x < 440 || mouse.x > 580 || mouse.y < 400 || mouse.y > 460)) {
            state->button_s.queding = 0;
            mouse_off(&mouse);
            bar1(440, 400, 580, 460, 0xC618); 
            bar2(440, 400, 580, 460, 0x000000);
            puthz(452, 405, "确定", 48,55, 0x000000);
            mouse_on(mouse);
        }

        if (mouse.x >= 965 && mouse.x <= 1024 && mouse.y >= 0 && mouse.y <= 53 && !state->button_s.xx) {
            state->button_s.xx=1;
            mouse_off(&mouse);
            bar1(965,0,1024,53,0xF800);
            Line_Thick(965,0,1024,53, 1,0x000000);
            Line_Thick(965,53,1024,0, 1,0x000000);
            mouse_on(mouse);
        } else if (state->button_s.xx && (mouse.x < 965 || mouse.x > 1024 || mouse.y < 0 || mouse.y > 53)) {
            state->button_s.xx = 0;
            mouse_off(&mouse);
            bar1(965,0,1024,53,0x340F);
            Line_Thick(965,0,1024,53, 1,0x000000);
            Line_Thick(965,53,1024,0, 1,0x000000);        
            mouse_on(mouse);
        }



		
        if(mouse_press(965,0,1024,53) == 1)
        {
            *puge=2;
            break;
        }
        if((mouse_press(340, 20, 480, 80) == 1)&&(i1==0))
		{
			handleStartButton(&i1, regions, &numRegions);
		}
	
			// 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷录锟?
		handle_region_click(&i1, regions, numRegions, map, T, &begin);
			
	
			// 锟斤拷锟斤拷锟秸碉拷选锟斤拷
		handleendButton(&i1, endRegions, &numEndRegions);


		handle_region_click_end(&i1, endRegions, &numEndRegions, &end);
		
		
		if((mouse_press(340, 170, 480, 230) == 1)&&(i1==4))
		{
			drawPath(&begin, &end,  T, &i1);
		}
		if((mouse_press(340, 170, 480, 230) == 1)&&(i1==5)){
			i1=0;
			mouse_off(&mouse);

			draw_autoguide();

			mouse_on(mouse);
		}

        if((end ==begin)&&(i1==4)){
            i1=6;
            bar1(236,202,775,530,0xC618);
            bar2(236,202,775,530,0x000000);
            Line2(236,220,775,220,0x000000);
            puthz(248,250,"请选择不同的起点和终点",48,45,0x000000);
            bar1(440, 400, 580, 460, 0xC618); 
            bar2(440, 400, 580, 460, 0x000000);
            puthz(452, 405, "确定", 48,55, 0x000000);
        }
        if(mouse_press(440, 400, 580, 460) == 1&&(i1==6)){
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

// 取得指定区域的 X 坐标
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
// 取得指定区域的 X 坐标
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
// 取得指定区域的 Y 坐标
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
// 取得指定区域的 Y 坐标
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
// 延时函数
void delayer(int ms) {
    long endTime = clock() + ms;
    while (clock() < endTime);
}
// 绘制自动导航界面
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
	bar1(64,295,173,359, 0x7BEF);//1锟??
    bar2(64,295,173,359,0x000000);
	bar1(65,631,189,742, 0x7BEF);//2锟??
    bar2(65,631,189,742,0x000000);
	bar1(223,506,344,599, 0x7BEF);//3锟?? 
    bar2(223,506,344,599,0x000000);
	bar1(436,330,612,426, 0x7BEF);//4锟??
    bar2(436,330,612,426,0x000000);
	bar1(450,630,605,727, 0x7BEF);//5锟??
	bar2(450,630,605,727,0x000000);
    bar1(819,316,959,427, 0x7BEF);//6锟??
    bar2(819,316,959,427,0x000000);
	bar1(825,624,962,730, 0x7BEF);//7锟??
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
	puthz(70,303,"一栋",48,45,0x000000);
	puthz(73,663,"二栋",48,45,0x000000);
	puthz(231,530,"三栋",48,45,0x000000);
	puthz(470,354,"四栋",48,45,0x000000);
	puthz(474,657,"五栋",48,45,0x000000);
	puthz(836,352,"六栋",48,45,0x000000);
	puthz(836,657,"七栋",48,45,0x000000);
	puthz(352,25,"起点",48,55,0x000000);
	puthz(352,100,"终点",48,55,0x000000);
	puthz(352,175,"取消",48,55,0x000000);
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
	bar1(965,0,1024,53,0x340F);
    Line_Thick(965,0,1024,53, 1,0x000000);
    Line_Thick(965,53,1024,0, 1,0x000000);
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
//Dijkstra
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


void handleStartButton(int *i1, ClickRegion regions[], int *numRegions) {
    if ((mouse_press(340, 20, 480, 80) == 1) && (*i1 == 0)) {
        initializeClickRegions(regions);
        *i1 = 1;
        
        // 等待鼠标释放
        do {
            MouseGet(&mouse);
            mouse_show(&mouse);
        } while ((mouse.key & 1) == 1);

        // 更新界面元素
        mouse_off(&mouse);
        bar1(340, 20, 480, 80, 0x340F);
        puthz(352, 25, "起点", 48, 55, 0x000000);
        puthz(531, 89, "请在左侧图中选择起点", 48, 45, 0x19E6);
        mouse_on(mouse);

        // 计算区域数量
        *numRegions = Max;  // 直接使用预定义的Max常量
    }
}

void handle_region_click(int *i1, ClickRegion *regions, int numRegions, 
	int map[Max][Max], TABLE T[], int *begin)
{
    int i,j;
    TABLE temp;

    for (i = 0; i < numRegions; i++) {
        if ((mouse_press(regions[i].x1, regions[i].y1, regions[i].x2, regions[i].y2)==1) && (*i1 == 1)) {
            do {
            MouseGet(&mouse);
            mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);

            _fmemcpy((int far *)map, (int far *)regions[i].map, (unsigned)(Max*Max*sizeof(int)));

            mouse_off(&mouse);
            bar1(340, 95, 480, 155, 0xFF44);
            puthz(352,100,"终点",48,55,0x000000);
            Circlefill(regions[i].x1+20,regions[i].y1+20,3,0xF800);
            bar1(515,82,1000,148,0x7FFE);
            mouse_on(mouse);

            Dijkstra(map,0, T);

            for(j=0;j<Max;j++){
                if(regions[i].start != 0 && T[j]->path == 0)
                T[j]->path += regions[i].start;
            }

            switch(regions[i].start){
                case 1: temp=T[0]; T[0]=T[1]; T[1]=temp; break;
                case 2: temp=T[0]; T[0]=T[2]; T[2]=temp; break;
                case 3: temp=T[0]; T[0]=T[3]; T[3]=temp; break;
                case 4: temp=T[0]; T[0]=T[4]; T[4]=temp; break;
                case 5: temp=T[0]; T[0]=T[5]; T[5]=temp; break;
                case 6: temp=T[0]; T[0]=T[6]; T[6]=temp; break;
            }

            *begin = regions[i].start;
            *i1 = 2;
            break;
        }
        else if(mouse_press(340, 170, 480, 230) == 1 && (*i1 == 1)) {
            *i1=0;
            mouse_off(&mouse);
            draw_autoguide();
            mouse_on(mouse);
            break;
        }
    }
}

void handleendButton(int *i1, ClickRegion endRegions[], int *numEndRegions){
	if((mouse_press(340, 95, 480, 155) == 1)&&(*i1==2))
		{
			initializeClickRegions(endRegions);

			*i1=3;
            // put_asc16_number_size(750,100,2,2,endRegions[6].start,0x000000);


			do {
				MouseGet(&mouse);
				mouse_show(&mouse);
			} while ((mouse.key & 1) == 1);

			mouse_off(&mouse);
			bar1(340, 95, 480, 155,0x340F);
			puthz(352,100,"终点",48,55,0x000000);
			puthz(531,89,"请在左侧图中选择终点",48,45,0x19E6);

			mouse_on(mouse);

				
			*numEndRegions = Max;
		}
		else if((mouse_press(340, 170, 480, 230) == 1)&&(*i1==2))
			{
				*i1=0;
				
			    mouse_off(&mouse);

				draw_autoguide();
			 
				mouse_on(mouse);
            
			}			 
	
}

void handle_region_click_end(int *i1, ClickRegion endRegions[], int *numEndRegions, int *end)
{

	int i;		
	for (i = 0; i < *numEndRegions; i++) {
		if ((mouse_press(endRegions[i].x1, endRegions[i].y1, endRegions[i].x2, endRegions[i].y2) == 1)&&(*i1==3)) {
			*i1=4;
			do {
			MouseGet(&mouse);
			mouse_show(&mouse);
			} while ((mouse.key & 1) == 1);
					
			*end = endRegions[i].start;
			// put_asc16_number_size(750,100,2,2,end,0x000000);
			mouse_off(&mouse);
			bar1(340, 170, 480, 230,0xFF44);
			puthz(352,175,"开始",48,55,0x000000);				
			bar1(515,82,1000,148,0x7FFE);
			Circlefill((endRegions[i].x1)+20,(endRegions[i].y1)+20,3,0xF800);
			mouse_on(mouse);

			break;
		}
        else if(mouse_press(340, 170, 480, 230) == 1 && (*i1 == 3)) {
            *i1=0;
            mouse_off(&mouse);
            draw_autoguide();
            mouse_on(mouse);
            break;
        }
    }
}

void drawPath(int *begin, int *end, TABLE T[], int *i1) {
    int j, k;
	 int time;
	 int path[Max];
	 int pathLength = 0;
	 int current = *end;
	 while (current != *begin) {
		 path[pathLength] = current;
		 pathLength++;
		 current = T[current]->path;
	 }
	 path[pathLength] = *begin;
	 pathLength++;
		 
			 // 锟斤拷转路锟斤拷锟斤拷使锟斤拷锟斤拷锟姐到锟秸碉拷
	 for (j= 0; j < pathLength / 2; j++) {
		 int temp = path[j];
		 path[j] = path[pathLength - j - 1];
		 path[pathLength - j - 1] = temp;
	 }
	 time=T[*end]->distance;
	 *i1=5;
			
		 
			 // 锟斤拷锟斤拷小锟斤拷锟斤拷锟斤拷
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
	puthz(531,89,"本次导航用时    分钟",48,45,0x19E6);
	bar1(801, 84, 890, 141,0x7FFE);
	put_asc16_number_size(820, 93,3,3,time,0xFFA5);
	bar1(340, 170, 480, 230,0xFF44);
    puthz(352,175,"完成",48,55,0x000000);
	mouse_on(mouse);
}

void button1(int x1, int y1, int x2, int y2, char *s, int *i) {
    // 验证输入参数
   

    if (mouse.x >= x1 && mouse.x <= x2 && mouse.y >= y1 && mouse.y <= y2 && !*i) {
        *i=1;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0x8410);
        puthz(x1 + 15, y1 + 8, s, 24, 26, 0X000000);
        mouse_on(mouse);
    } else if (*i && (mouse.x < x1 || mouse.x > x2 || mouse.y < y1 || mouse.y > y2)) {
        *i = 0;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0xC618);
        puthz(x1 + 15, y1 + 8, s, 24, 26, 0X000000);
        mouse_on(mouse);
    }
}

void button2(int x1, int y1, int x2, int y2, char *s, int *i) {
    // 验证输入参数
   

    if (mouse.x >= x1 && mouse.x <= x2 && mouse.y >= y1 && mouse.y <= y2 && !*i) {
        *i=1;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0x8410);
        puthz(x1 + 30, y1 + 25, s, 24, 30, 0X000000);
        mouse_on(mouse);
    } else if (*i && (mouse.x < x1 || mouse.x > x2 || mouse.y < y1 || mouse.y > y2)) {
        *i = 0;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0xC618);
        puthz(x1 + 30, y1 + 25, s, 24, 30, 0X000000);
        mouse_on(mouse);
    }
}

void button3(int x1, int y1, int x2, int y2, char *s, int *i) {
    // 验证输入参数
   

    if (mouse.x >= x1 && mouse.x <= x2 && mouse.y >= y1 && mouse.y <= y2 && !*i) {
        *i=1;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0x8410);
        puthz(x1 + 30, y1 + 25, s, 24, 30, 0xF800);
        mouse_on(mouse);
    } else if (*i && (mouse.x < x1 || mouse.x > x2 || mouse.y < y1 || mouse.y > y2)) {
        *i = 0;
        mouse_off(&mouse);
        bar1(x1, y1, x2, y2, 0xC618);
        puthz(x1 + 30, y1 + 25, s, 24, 30, 0xF800);
        mouse_on(mouse);
    }
}

void button4(int x1, int y1, int r, char s, int *i) {

    // 验证输入参数
   

    if (mouse.x >= x1-r && mouse.x <= x1+r && mouse.y >= y1-r && mouse.y <= y1+r && !*i) {
        *i=1;
        mouse_off(&mouse);
        Circlefill(x1,y1,r-2,0x8410);
		Put_Asc16_Size(x1-10,y1-16,2,2,s,0x000000);
        mouse_on(mouse);
    } else if (*i && (mouse.x < x1-r || mouse.x > x1+r || mouse.y < y1-r || mouse.y > y1+r)) {
        *i = 0;
        mouse_off(&mouse);
        Circlefill(x1,y1,r,0xC618);
		Put_Asc16_Size(x1-10,y1-16,2,2,s,0x000000);
        mouse_on(mouse);
    }
}

void button5(int x1, int y1, int x2, int y2,  int *i) {
    // 验证输入参数
   

    if (mouse.x >= x1 && mouse.x <= x2 && mouse.y >= y1 && mouse.y <= y2 && !*i) {
        *i=1;
        mouse_off(&mouse);
        bar1(603,600,633,630,0xF800);
        Line2(603,600,633,600,0xFFFFFF);
        Line2(603,600,603,630,0xFFFFFF);
        Line2(603,600,633,630,0xFFFFFF);
        Line2(633,600,603,630,0xFFFFFF);
        mouse_on(mouse);
    } else if (*i && (mouse.x < x1 || mouse.x > x2 || mouse.y < y1 || mouse.y > y2)) {
        *i = 0;
        mouse_off(&mouse);
        bar1(603,600,633,630,0x000000);
        Line2(603,600,633,600,0xFFFFFF);
        Line2(603,600,603,630,0xFFFFFF);
        Line2(603,600,633,630,0xFFFFFF);
        Line2(633,600,603,630,0xFFFFFF);
        mouse_on(mouse);
    }
}