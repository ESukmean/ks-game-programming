#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void display_rule(void);
void gotoxy(int x, int y);
void make_treasure(int tx[], int ty[]);
void display_map(int matrix[][10], int tx[], int ty[]);
void basic_map(void);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);
void game_control(int tx[], int ty[]);

int main(void)
{
    int tx[2], ty[2];
	int matrix[10][10]={0};
    clock_t start, end;
    double pst;
    srand(time(NULL));
	make_treasure(tx, ty);
    display_rule();
    start=clock();
	system("cls");
    game_control(tx, ty);
    end=clock();
	pst=(double)(end-start)/CLK_TCK;
	gotoxy(1, 13);
	printf("경과 시간 : %.1f 초", pst);
	gotoxy(1, 14);
	printf("모두 찾았습니다. 게임을 종료합니다. \n");
	getch();
	return 0;
}

void display_rule(void)
{
	gotoxy(1, 1);
	printf("보물찾기");
	gotoxy(1,3);
	printf("아래의 바둑판 모양의 격자에는 보물이 \n");
	gotoxy(1,4);
	printf("숨겨져 있습니다. \n");
	gotoxy(1,5);
	printf("화살표(↑↓←→)키를 움직여서 찾습니다. \n");
	gotoxy(1,7);
	basic_map();
	printf("\n아무키나 누르면 시작합니다. \n");
	getch();
}

void basic_map(void)
{
	int i, j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("■");
		printf("\n");
	}
}


void make_treasure(int tx[], int ty[])
{
	int i;
    for(i=0;i<2;i++)
    {
		do
		{
			tx[i]=rand()%11; //보물의 x좌표
			ty[i]=rand()%11; //보물의 y좌표
		}while((tx[i]<=1) || (ty[i]<=1));  
     }
}



void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void display_map(int matrix[][11], int tx[], int ty[])
{
	int i, j;
	basic_map();
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
			if (matrix[i][j]==1)
			{
				gotoxy(2*i-1, j);
				printf("□");
			}
			else if (matrix[i][j]==2)
			{
				gotoxy(2*i-1, j);
				printf("★");
			}	
}
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //위쪽(상) 방향의 화살표 키 입력
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y좌표의 최소값
		break;
	case 75:  //왼쪽(좌) 방향의 화살표 키 입력
		*x1=*x1-2;            //x좌표의 감소값
		if (*x1<1)	*x1=1; //x좌표의 최소값
		break;
	case 77:  //오른쪽(우) 방향의 화살표 키 입력
		*x1=*x1+2;               //x좌표의 증가값
		if (*x1>x_b)  *x1=x_b; //x좌표의 최대값
		break;
	case 80:  //아래쪽(하) 방향의 화살표 키 입력
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y좌표의 최대값
		break;
	default:
		return;
	}
}

void game_control(int tx[], int ty[])
{
	char key;
	int i, j, count=0;
	int x=1, y=1;
	int matrix[11][11]={0};
	do
	{
		gotoxy(x, y);
		printf("□");
		matrix[(x+1)/2][y]=1;

		for(i=0;i<2;i++)
			if (((x+1)/2==tx[i]) && (y==ty[i]))
				matrix[(x+1)/2][y]=2;

		gotoxy(1, 1);
		display_map(matrix, tx, ty);

		count=0;
		for(i=1;i<=10;i++)
			for(j=1;j<=10;j++)
				if (matrix[i][j]==2)
					count=count+1;
		gotoxy(1,12);
   		printf("찾은 보물(★)의 개수 : %d", count);
		key=getch();
		move_arrow_key(key, &x, &y, 19, 10);
	}while(count<2);
}
