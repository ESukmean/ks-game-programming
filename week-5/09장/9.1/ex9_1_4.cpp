#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void draw_check02(int c, int r);
void display_piano_keyboard(void);
void touch_keyboard(int code);
void display_manual(void);
void practice_piano(void);
int calc_frequency(int octave, int inx);  //음계의 주파수 계산


void gotoxy(int x, int y);
void music_paper(void);     //오선지 표시
void note(int i, int x);   //음표 표시
 
int main(void)
{
	display_manual();
	practice_piano();
	gotoxy(1, 22);
	return 0;
}

void display_manual(void)
{
	printf("키보드의 숫자를 누르면 해당 건반에 음이 건반과 악보에 표시되고,\n");
	printf("해당 음이 스피커로 출력됩니다. 프로그램 종료는 Esc 키 입니다.\n");
}
void practice_piano(void)
{
	int index[]={0, 2, 4, 5, 7, 9, 11, 12};
	int freq[8], code, i, count=0;
	for(i=0;i<8;i++)
		freq[i]=calc_frequency(4, index[i]); //주파수계산
	draw_check02(8, 2);
	display_piano_keyboard();  //화면에 건반표시
	music_paper();
	do
	{
		gotoxy(2, 7);
		code=getch();
		if ('1'<=code && code<='11')
		{
			code-=49;
			touch_keyboard(code);  //누른 건반에 ▲표시
			Beep(freq[code],300);
		        display_piano_keyboard(); //화면에 건반표시
			if (count>17)
			{
				music_paper();
				count=0;
			}
			note(code+1, count*4+1);
			count++;
		}
	}while(code!=27);
}
void draw_check02(int c, int r)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++)
	b[i]=0xa0+i;
    printf("%c%c",a, b[3]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
	{
		printf("  ");
		printf("%c%c",a, b[2]);
	}
	printf("\n");
	printf("%c%c", a, b[7]);
	for(j=0;j<c-1;j++)
	{
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[11]);
	}
	printf("%c%c",a, b[1]);
	printf("%c%c",a, b[9]);
	printf("\n");
    }
    printf("%c%c", a, b[2]);
    for(j=0;j<c;j++)
    {
	printf("  ");
	printf("%c%c",a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}
void display_piano_keyboard(void)
{
	int i;
	char code[8][4]={"도","레","미","파","솔","라","시","도"};
	for(i=0;i<8;i++)
	{
		gotoxy(3+i*4,4);
		printf("%2d", i+1); 
	}
	for(i=0;i<8;i++)
	{
		gotoxy(3+i*4,6);
		printf("%s", code[i]);
	}
}
void touch_keyboard(int code)
{
	gotoxy(3+code*4,6);
	printf("%c%c", 0xa1, 0xe3);
}
int calc_frequency(int octave, int inx)
{
	double do_scale=32.7032;
	double ratio=pow(2., 1/12.), temp;
	int i;
	temp=do_scale*pow(2, octave-1);
	for(i=0;i<inx;i++)
	{
		temp=(int)(temp+0.5);
		temp*=ratio;
	}
	return (int) temp;
}


void music_paper(void)
{
	unsigned char a6=0xa6;
	unsigned char line=0xa1;
	int i, j;
	gotoxy(1, 8);   //악보 clear
	for(i=1;i<15;i++)
	{
		for(j=1;j<=78;j++)
			printf(" ");
		printf("\n");
	}
	gotoxy(1, 8);
	for(j=1;j<6;j++)
	{
		for(i=1;i<=35;i++)
			printf("%c%c", a6, line);
		printf("\n\n");
	}
}

void note(int i, int x)
{
	unsigned char a1=0xa1;
	unsigned char circle=0xdb;
	int y;
	y=19-i;
	gotoxy(x, y);
	printf("%c%c\n", a1, circle);
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
