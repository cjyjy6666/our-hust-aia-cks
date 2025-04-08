#include"allfunc.h"

void music(CarStatus *state,int *puge)
{
	char mus[7][15]={'\0'};//¸èÃû²»³¬¹ý13×Ö·û
    const int LINES=count_music();
    int pos=0;//postion=index of first line to show
    int select=0;//selected line
    int i;
    read_music(mus,pos);
	mouse_off(&mouse);
    draw_music_page(state);
    display_music(mus,select);
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
        if (mouse_press(270,60,300,95) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            if(pos>0)
            {
                pos--;
                select++;
                read_music(mus,pos);
                display_music(mus,select);
            }
        }
        if (mouse_press(270,410-95,300,410-60) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            if(pos<LINES-7)
            {
                pos++;
                select--;
                read_music(mus,pos);
                display_music(mus,select);
            }
        }
        if (mouse_press(433,190,533,260) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            if(state->media_s.mus_ord==0)
            {
                state->media_s.mus_ord=1;
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "ÂÒÐò",24,30,0xFFFFFF);
            }
            else if(state->media_s.mus_ord==1)
            {
                state->media_s.mus_ord=2;
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "Ñ­»·",24,30,0xFFFFFF);
            }
            else if(state->media_s.mus_ord==2)
            {
                state->media_s.mus_ord=0;
                bar1(434,191,532,259,0x0085);
                puthz(463, 215, "Ë³Ðò",24,30,0xFFFFFF);
            }
        }
        if (mouse_press(433,290,533,360) == 1)
		{
			do 
            {
                MouseGet(&mouse);
                mouse_show(&mouse);
            } while ((mouse.key & 1) == 1);
            if(state->media_s.music==-1)
            {
                state->media_s.music=select+pos;
            }
            else
            state->media_s.music=-1;
            if(state->media_s.music==-1)
            {
                bar1(434,291,532,359,0x0085);
                puthz(463, 315, "²¥·Å",24,30,0xFFFFFF);
            }
            else
            {
                bar1(434,291,532,359,0x0085);
                puthz(463, 315, "ÔÝÍ£",24,30,0xFFFFFF);
            }
        }
        for(i=0;i<7;i++)
        {
            if (mouse_press(20,65+40*i,250,105+40*i) == 1)
            {
                do 
                {
                    MouseGet(&mouse);
                    mouse_show(&mouse);
                } while ((mouse.key & 1) == 1);
                select=i;
                display_music(mus,select);
                state->media_s.music=select;
                if(state->media_s.music==-1)
                {
                    bar1(434,291,532,359,0x0085);
                    puthz(463, 315, "²¥·Å",24,30,0xFFFFFF);
                }
                else
                {
                    bar1(434,291,532,359,0x0085);
                    puthz(463, 315, "ÔÝÍ£",24,30,0xFFFFFF);
                }
            }
        }
    }
}

void draw_music_page(CarStatus *state)
{
    Line2(603,600,633,600,0xFFFFFF);
	Line2(603,600,603,630,0xFFFFFF);
	Line2(603,600,633,630,0xFFFFFF);
	Line2(633,600,603,630,0xFFFFFF);

    bar2(433,190,533,260,0xFFFFFF);
	bar2(433,290,533,360,0xFFFFFF);

    if(state->media_s.mus_ord==0)
    {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "Ë³Ðò",24,30,0xFFFFFF);
    }
    else if(state->media_s.mus_ord==1)
    {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "ÂÒÐò",24,30,0xFFFFFF);
    }
    else if(state->media_s.mus_ord==2)
    {
        bar1(434,191,532,259,0x0085);
        puthz(463, 215, "Ñ­»·",24,30,0xFFFFFF);
    }

    if(state->media_s.music==-1)
    {
        bar1(434,291,532,359,0x0085);
        puthz(463, 315, "²¥·Å",24,30,0xFFFFFF);
    }
    else
    {
        bar1(434,291,532,359,0x0085);
        puthz(463, 315, "ÔÝÍ£",24,30,0xFFFFFF);
    }

    
    bar2(20,60,250,350,0xFFFFFF);
    bar2(19,59,251,351,0xFFFFFF);
    
    Line2(285,60,270,80,0xFFFFFF);
    Line2(270,80,278,80,0xFFFFFF);
    Line2(278,80,278,95,0xFFFFFF);
    Line2(278,95,292,95,0xFFFFFF);
    Line2(292,95,292,80,0xFFFFFF);
    Line2(292,80,300,80,0xFFFFFF);
    Line2(300,80,285,60,0xFFFFFF);
    
    Line2(285,410-60,270,410-80,0xFFFFFF);
    Line2(270,410-80,278,410-80,0xFFFFFF);
    Line2(278,410-80,278,410-95,0xFFFFFF);
    Line2(278,410-95,292,410-95,0xFFFFFF);
    Line2(292,410-95,292,410-80,0xFFFFFF);
    Line2(292,410-80,300,410-80,0xFFFFFF);
    Line2(300,410-80,285,410-60,0xFFFFFF);
    
    Line2(20,65,250,65,0xFFFFFF);
    Line2(20,105,250,105,0xFFFFFF);
    Line2(20,145,250,145,0xFFFFFF);
    Line2(20,185,250,185,0xFFFFFF);
    Line2(20,225,250,225,0xFFFFFF);
    Line2(20,265,250,265,0xFFFFFF);
    Line2(20,305,250,305,0xFFFFFF);
    Line2(20,345,250,345,0xFFFFFF);
    bar1(21,66,249,104,0x0085);
    bar1(21,106,249,144,0x0085);
    bar1(21,146,249,184,0x0085);
    bar1(21,186,249,224,0x0085);
    bar1(21,226,249,264,0x0085);
    bar1(21,266,249,304,0x0085);
    bar1(21,306,249,344,0x0085);
}

int count_music()
{
    FILE *fp;
    int total=0;
    char buffer[15];
    fp=fopen("data\\music.txt","r");
    while(fgets(buffer,sizeof(buffer),fp))
    {
        total++;
    }
    fclose(fp);
    return total;
}

void read_music(char mus[7][15],int pos)
{
    FILE *fp;
    int i,j;
    int newline_pos;
    char buffer[15];
    fp=fopen("data\\music.txt","r");
    rewind(fp);
    for(i=0;i<pos;i++)
    {
        fgets(buffer,sizeof(buffer),fp);
    }
    for(j=pos;j<pos+7;j++)
    {
        if(fgets(buffer,sizeof(buffer),fp))
        {
            //delete \n
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
            strcpy(mus[j-pos],buffer);
        }
        else
        {
            mus[j-pos][0]='\0';//if no more lines
        }
    }
    fclose(fp);
}

void display_music(char mus[7][15],int select)
{
    int i;
    for(i=0;i<7;i++)
    {
        if(mus[i][0]!='\0')
        {
        bar1(21,66+i*40,249,104+i*40,0x0085);
        //put_asc16_size(25,69+i*40,2,2,num[i],0xFFFFFF);
        prt_hz24_asc32(25,69+i*40,mus[i],0xFFFFFF,"HZK\\Hzk24f");
        }
        else
        bar1(21,66+i*40,249,104+i*40,0x0085);
        if(i==select)
        {
            mouse_off(&mouse);
            bar1(21,66+i*40,249,104+i*40,0x7FFF);
            //put_asc16_size(25,69+i*40,2,2,mus[i],0xFFFFFF);
            prt_hz24_asc32(25,69+i*40,mus[i],0xFFFFFF,"HZK\\Hzk24f");
            mouse_on(mouse);
        }
    }
}