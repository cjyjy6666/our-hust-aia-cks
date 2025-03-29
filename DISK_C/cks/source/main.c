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
		case 8:
			draw_mainpage(&state);
			media(&state,&puge);
			break;
		case 9:
			draw_mainpage(&state);
			phone(&state,&puge);
			break;
		case 10:
			draw_mainpage(&state);
			contact(&state,&puge);
			break;
		default:
			break;
		}

	}
	CloseSVGA();
}
