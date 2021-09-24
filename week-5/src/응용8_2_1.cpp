#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void control_scoreboard(int st,int end,int r[],int h[],int e[], int b[]);
void display_scoreboard(int r[], int h[], int e[], int b[]);
void draw_check02(int c, int r);
void gotoxy(int x, int y);
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void)
{
	int  baseball[12][2]={0},r[2]={0},h[2]={0},e[2]={0},b[2]={0};
	display_scoreboard(r, h, e, b);	
	control_scoreboard(1, 9, r, h, e, b);
	control_scoreboard(10, 12, r, h, e, b);
	gotoxy(1, 15);
	printf("무승부입니다. 아무키나 누르시오\n");
	getch();
	return 0;
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

void display_scoreboard(int r[], int h[], int e[], int b[])
{
	int i, j;
	printf("스코어보드 \n");
	draw_check02(17, 3);
	for(i=1;i<=12;i++)
	{
		gotoxy(i*4+3, 3);
		printf("%2d", i);
	}
	gotoxy(13*4+4, 3);
	printf("R");
	gotoxy(14*4+4, 3);
	printf("H");
	gotoxy(15*4+4, 3);
	printf("E");
	gotoxy(16*4+4, 3);
	printf("B");
	gotoxy(3, 5);
	printf("CL");
	gotoxy(3, 7);
	printf("TG");
	for(j=0;j<=1;j++)
	{
		gotoxy(13*4+3, 5+2*j);
		printf("%2d", r[j]);
		gotoxy(14*4+3, 5+2*j);
		printf("%2d", h[j]);
		gotoxy(15*4+3, 5+2*j);
		printf("%2d", e[j]);
		gotoxy(16*4+3, 5+2*j);
		printf("%2d", b[j]);
	}
}
void control_scoreboard(int st,int end, int r[], int h[], int e[], int b[])
{
   int i, j, k, rr, hh, ee, bb;
   char state[3];
   for(i=st;i<=end;i++)
   {
 	for(j=0;j<=1;j++)
	{
		if (j==0)
			strcpy(state, "초");
		else
			strcpy(state, "말");
		gotoxy(i*4+3, 5+2*j);
		printf("%2d", 0);
		gotoxy(1, 10);
		printf("%d회%s 결과 ", i, state);
		gotoxy(1, 11);

		printf("안타수 입력 : ");
		scanf("%d", &hh);
		h[j]+=hh;
		gotoxy(14*4+3, 5+2*j);
		printf("%2d", h[j]);
		gotoxy(1, 12);

		printf("실책수 입력 : ");
		scanf("%d", &ee);
		e[j]+=ee;
		gotoxy(15*4+3, 5+2*(1-j));
		printf("%2d", e[j]);

		gotoxy(1, 13);
		printf("포볼수 입력 : ");
		scanf("%d", &bb);
		b[j]+=bb;
		gotoxy(16*4+3, 5+2*j);
		printf("%2d", b[j]);
		gotoxy(1, 14);
		printf("점수   입력 : ");
		scanf("%d", &rr);
		r[j]+=rr;
		gotoxy(13*4+3, 5+2*j);
		printf("%2d", r[j]);

		gotoxy(i*4+3, 5+2*j);
		printf("%2d", rr);

		gotoxy(1, 15);
		printf("아무키나 누르시오....");
		getch();
		for(k=10; k<=15; k++)
		{
			gotoxy(1, k);
		    	printf("                       ");
		}
		if (9<=i&&((j==0&& r[0]<r[1]) || (j==1 && r[0]!=r[1])))
		{
			gotoxy(1, 15);
			printf("경기가 끝났습니다. 아무키나 누르시오\n");
			getch();
			exit(0);
		}
	}
   }
}
