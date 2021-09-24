#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y);
int draw_horizontal_slide(int x, int y, int length, char *s);
int draw_vertical_slide(int x, int y, int length, char *s);
void draw_rectangle(int c, int r);
void draw_pin(void);
void draw_ball(int x, int y);

void game_control(int x, int y, int v_slide_length, int h_slide_length, int temp, char *slide, char key);

#define X_MAX 29
#define Y_MAX 10 

int main(void)
{
	char *slide="■", key;
	int x, y, temp;
	int h_slide_length=50, v_slide_length=10;

	x=y=1;

	system("cls");

	y=draw_vertical_slide(1, y, v_slide_length, slide);
	x=draw_horizontal_slide(x, v_slide_length+3, h_slide_length, slide);
	draw_pin();
	gotoxy(1, 16);
	printf("아무키나 누르면 시작합니다.");
	key=getch();
	temp=1;
	game_control(x, y, v_slide_length, h_slide_length, temp, slide, key);


	key=getch();
	return 0;
}


void game_control(int x, int y, int v_slide_length, int h_slide_length, int temp, char *slide, char key)
{
	gotoxy(1, 16);
	printf("아무키나 누르면 시작위치를 결정합니다.");
	do
	{
		y+=temp;
		if (y>9)
			temp=-1;
		else if (y<2)
			temp=1;
		Sleep(50);
		y=draw_vertical_slide(1, y, v_slide_length, slide);
	}while(!kbhit());

	key=getch();
	temp=1;
	gotoxy(1, 16);
	printf("아무키나 누르면 힘의 세기를 결정합니다.");
	do
	{
		x+=temp;
		if (x>49)
			temp=-1;
		else if (x<2)
			temp=1;
		Sleep(20);
		x=draw_horizontal_slide(x, v_slide_length+3, h_slide_length, slide);
	}while(!kbhit());

	draw_ball(x, y);
	gotoxy(1, 16);
	printf("\ngame over!\n");
}



void draw_ball(int x, int y)
{
	int i;
	gotoxy(7, y+1);
	printf("●");
	Sleep(100);
	for(i=7;i<=x+2;i++)
	{
		Sleep(30);
		gotoxy(i, y+1);
		printf("●");
	}
}


int draw_horizontal_slide(int x, int y, int length, char *s)
{
		int real_length=length/2;
		gotoxy(1, y);
		draw_rectangle(real_length+1, 1);
		gotoxy(x+2, y+1);
		printf("%s", s);
		gotoxy(real_length*2+2, y-1);
		printf("%2d", x);
		return x;
}

int draw_vertical_slide(int x, int y, int length, char *s)
{
		gotoxy(x, 1);
		draw_rectangle(1, length);
		gotoxy(x+2, y+1);
		printf("%s", s);
		gotoxy(x+6, length+1);
		printf("%2d", y);
		return y;
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_rectangle(int c, int r)
{
   int i, j;
   unsigned char a=0xa6;
   unsigned char b[7]; 
   for(i=1;i<7;i++)
	b[i]=0xa0+i;
   printf("%c%c",a, b[3]);
   for(i=0;i<c;i++)
	printf("%c%c", a, b[1]);
   printf("%c%c", a, b[4]);
   printf("\n");

   for(i=0;i<r;i++)
   {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
		printf("  ");
	printf("%c%c",a, b[2]);
	printf("\n");
   }

   printf("%c%c", a, b[6]);
   for(i=0;i<c;i++)
	printf("%c%c", a, b[1]);
   printf("%c%c", a, b[5]);
   printf("\n");
}


void draw_pin(void)
{
	gotoxy(50, 3);
	printf("●");
	gotoxy(48, 4);
	printf("●");
	gotoxy(46, 5);
	printf("●");
	gotoxy(50, 5);
	printf("●");
	gotoxy(44, 6);
	printf("●");
	gotoxy(48, 6);
	printf("●");
	gotoxy(46, 7);
	printf("●");
	gotoxy(50, 7);
	printf("●");
	gotoxy(48, 8);
	printf("●");
	gotoxy(50, 9);
	printf("●");
}

