#include"allfunc.h"

void phone(CarStatus *state,int *puge)
{
    FILE *fp;
    static char ph_num[13]={'\0'};
    static int num_len=0;
    int exists=0;
    char buffer[13];
    int newline_pos=-1;//to find \n
    int i;//in for
	mouse_off(&mouse);
    draw_phone_page(state);
    mouse_on(mouse);

    while(1)
    {
        show_all(state);
		mouse_show(&mouse);
        if (mouse_press(603,600,633,630) == 1)
		{
			*puge = 8;
			break;
		}
        key_det(ph_num,&num_len);
        if (mouse_press(433,190,533,260) == 1)//call
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            state->media_s.on_call^=1;
            state->media_s.call_second=0;
            if(state->media_s.on_call)
            {
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "挂断",24,30,0xF800);
            }
            else
            {
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "拨打",24,30,0xFFFFFF);
            }
        }
        if (mouse_press(433,290,533,360) == 1)//save
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            fp=fopen("data\\phone.dat","a+");
            //check if the number already exists in the file
            exists=0;
            rewind(fp);
            while(fgets(buffer,sizeof(buffer),fp))
            {
                newline_pos=-1;
                for(i=0;i<sizeof(buffer)+1;i++)
                {
                    if(buffer[i]=='\n')
                    {
                        newline_pos=i;
                        break;
                    }
                }
                if(newline_pos!=-1)
                {
                    buffer[newline_pos]='\0';//replace \n with \0
                }
                else
                {
                    buffer[12]='\0';//if no \n
                }
                if(strcmp(buffer,ph_num)==0)
                {
                    exists=1;
                    break;
                }
            }
            
            //then save the number
            if(!exists)
            {
                fprintf(fp,"%s\n",ph_num);
                bar1(241,91,619,149,0x0085);
                prt_hz24_asc32(322,104,"保存成功",0xFC44,"HZK\\Hzk24f");

            }
            else
            {
                bar1(241,91,619,149,0x0085);
                prt_hz24_asc32(322,104,"号码已存在",0xFC44,"HZK\\Hzk24f");
            }
            fclose(fp);
            num_len=0;
            ph_num[0]='\0';
        }
    }
}

void draw_phone_page(CarStatus *state)
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);

    Circle(60,130,20,0xFFFFFF);
    Circle(130,130,20,0xFFFFFF);
    Circle(200,130,20,0xFFFFFF);
    Circle(60,200,20,0xFFFFFF);
    Circle(130,200,20,0xFFFFFF);
    Circle(200,200,20,0xFFFFFF);
    Circle(60,270,20,0xFFFFFF);
    Circle(130,270,20,0xFFFFFF);
    Circle(200,270,20,0xFFFFFF);
    Circle(60,340,20,0xFFFFFF);
    Circle(130,340,20,0xFFFFFF);
    Circle(200,340,20,0xFFFFFF);
    Put_Asc16_Size(50,114,2,2,'1',0xFFFFFF);
    Put_Asc16_Size(120,114,2,2,'2',0xFFFFFF);
    Put_Asc16_Size(190,114,2,2,'3',0xFFFFFF);
    Put_Asc16_Size(50,184,2,2,'4',0xFFFFFF);
    Put_Asc16_Size(120,184,2,2,'5',0xFFFFFF);
    Put_Asc16_Size(190,184,2,2,'6',0xFFFFFF);
    Put_Asc16_Size(50,254,2,2,'7',0xFFFFFF);
    Put_Asc16_Size(120,254,2,2,'8',0xFFFFFF);
    Put_Asc16_Size(190,254,2,2,'9',0xFFFFFF);
    Put_Asc16_Size(50,324,2,2,'#',0xFFFFFF);
    Put_Asc16_Size(120,324,2,2,'0',0xFFFFFF);
    Put_Asc16_Size(190,324,2,2,'X',0xFFFFFF);
    bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);
    //call
    if(state->media_s.on_call)
    {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "挂断",24,30,0xF800);
    }
    else
    {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "拨打",24,30,0xFFFFFF);
    }
    puthz(463, 315, "存号",24,30,0xFFFFFF); //save
    bar2(240,90,620,150,0xFC44);
    bar1(241,91,619,149,0x0085);
}

void key_det(char ph_num[13],int *num_len)
{
    int x;
    if(*num_len<12)
    {
        if (mouse_press(40,110,80,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='1';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(110,110,150,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='2';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(180,110,220,150) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='3';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(40,180,80,220) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='4';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(110,180,150,220) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='5';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(180,180,220,220) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='6';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(40,250,80,290) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='7';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(110,250,150,290) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='8';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(180,250,220,290) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='9';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if (mouse_press(110,320,150,360) == 1)
		{
			do {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            ph_num[(*num_len)++]='0';
            ph_num[*num_len]='\0';
            bar1(241,91,619,149,0x0085);
            x=240+(380-16*(*num_len))/2;
            put_asc16_size(x,104,2,2,ph_num,0xFC44);
		}
        if(*num_len>0)
        {
            if (mouse_press(180,320,220,360) == 1)
            {
                do 
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                ph_num[--(*num_len)]='\0';
                bar1(241,91,619,149,0x0085);
                x=240+(380-16*(*num_len))/2;
                put_asc16_size(x,104,2,2,ph_num,0xFC44);
            }
        }
        
    }
    else 
    {
        bar1(241,91,619,149,0x0085);
        prt_hz24_asc32(322,104,"号码应为11位!",0xFC44,"HZK\\Hzk24f");
        while(mouse.key & 1)
            MouseGet(&mouse);
        *num_len = 0;
        ph_num[0] = '\0';
    }
}