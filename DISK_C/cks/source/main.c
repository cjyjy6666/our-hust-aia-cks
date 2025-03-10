#include <allfunc.h>

void main()
{      
	CarStatus state= {0};
	int puge = 0;
	//init_car_status();
	//初始化车辆状态
	SetSVGA64k();
	
	mouse_init();
	
	while (1)
	{
		switch (puge)
		{
		case 0:
			welcome(&puge);
			break;
		case 2:
			mainpage(&state,&puge);
			break;
		case 3:
			light(&state,&puge);
			break;
		case 4:
			ac(&state,&puge);
			break;
		case 5:
			autoguide(&state,&puge);
			break;
		default:
			break;
		}

	}
	CloseSVGA();
}


//�����ʿ���
//ʯ����ѧ����qq��1092957376
//�Թ���ѧ����qq��2945322359