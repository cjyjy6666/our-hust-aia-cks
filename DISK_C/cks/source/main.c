#include <allfunc.h>

void main()
{      

	int puge = 0;

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
			mainpage(&puge);
			break;
		case 3:
			light(&puge);
			break;
		case 4:
			ac(&puge);
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