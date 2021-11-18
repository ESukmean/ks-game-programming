//리버시 게임
//현재 program은 리버시 게임의 초기화면과 돌의 움직임 만을 표현
//같은 자리에 돌을 놓을 수 없음

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check02(int c, int r);
void game_control(void);
void display_stone(int matrix[][9][9]);

int main(void)
{
	game_control();
	return 0;
}


void game_control(void)
{
	int x=3, y=2, other=0; 
	int matrix[2][9][9]={0};
	char key, *stone[2]={"○", "●"};
	matrix[0][4][4]=1;
	matrix[0][5][5]=1;
	matrix[1][4][5]=1;
	matrix[1][5][4]=1;

	do
	{
		gotoxy(1,1);
		draw_check02(8, 8);
		display_stone(matrix);
		gotoxy(x, y);
		printf("%s", stone[other]);
		gotoxy(1, 18);
		printf("방향키로 움직이고 ");
		printf("스페이스 키를 누르시오.");
		gotoxy(1, 19);
        printf("돌을 놓았으면 상대방 차례입니다. ");
		while(!kbhit());
		key=getch();
		if (key>71)
			move_arrow_key(key, &x, &y, 31, 16);
		else if(key==32)
		{
			if ((matrix[0][(x+1)/4][y/2]) || (matrix[1][(x+1)/4][y/2]))
			{
				gotoxy(1,21);
				printf("이미 돌이 있습니다.              \a");
				continue;
			}
			else
			{
				matrix[other][(x+1)/4][y/2]=1;
				other=1-other;
				gotoxy(1,21);
				printf("                                    ");

			}
		}
/*
		display_stone(matrix);
		gotoxy(x, y);
		printf("%s", stone[other]);
*/
	}while(1);
}

void display_stone(int matrix[][9][9])
{
	int i, x, y;
	char  *stone[2]={"○", "●"};

	for(i=0;i<2;i++)
		for(x=1;x<9;x++)
			for(y=1;y<9;y++)
			{
				if (matrix[i][x][y]==1)
				{
					gotoxy(x*4-1, y*2);
					printf("%s", stone[i]);
				}
			}
}


void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:
		*y1=*y1-2;
		if (*y1<=2)	*y1=2;
		break;
	case 75:
		*x1=*x1-4;
		if (*x1<=3)	*x1=3;
		break;
	case 77:
		*x1=*x1+4;
		if (*x1>x_b)  *x1=x_b;
		break;
	case 80:
		*y1=*y1+2;
		if (*y1>y_b)  *y1=y_b;
		break;
	default:
		return;
	}
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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

