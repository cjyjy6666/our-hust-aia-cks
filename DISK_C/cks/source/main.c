#include <allfunc.h>

void main()
{      
	CarStatus state= {0};
	int puge = 0;
	init_car_status(&state);
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
		case 6:
			wiper(&state,&puge);
			break;
		case 7:
			drive(&state,&puge);
			break;
		default:
			break;
		}

	}
	CloseSVGA();
}
