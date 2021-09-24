//돌이 이미 놓여있는 위치에 다른 돌을 놓을 수 없다.
//돌을 놓을때 걸리는 시간을 제어하는 방법
// [방법 1] 한사람이 돌을 놓고나서 다른 사람이 돌을 놓을때까지 시간을 제어
//          예를 들어 돌을 움지이지 않고, 가만히 있는 상황에서 제한시간 5초를 넘기면 다른 사람에게 기회가 돌아감.
// [방법 2] 각 사람에 대해 돌을 놓을 수 있는 시간을 제어
//          예로 한 사람에게 전체 20분 내에 두도록 하여 소비한 시간을 표시
// 여기에서는 [방법 1]을 사용함.
// 해결해야할 문제는 돌을 움직이는 상황에서도 시간체크를 해야 함.
 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>       //시간

#define TIME_LIMIT 5   //제한시간 5초 

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);
void display_stone(int matrix[][20][20]);

int main(void)
{
	game_control();
	return 0;
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_check01(int c, int r)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++)
	b[i]=0xa0+i;
    printf("%c%c",a, b[3]);
    for(i=0;i<c-1;i++)
	 printf("%c%c", a, b[8]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[7]);
	for(j=0;j<c-1;j++)
	    printf("%c%c", a, b[11]);
	printf("%c%c",a, b[9]);
	printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c-1;i++)
	printf("%c%c", a, b[10]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void game_control(void)
{
	int x=1, y=1, other=0; 
	int matrix[2][20][20]={0};
	char key;
	char *stone[2]={"○","●"};
	clock_t start, end;
	double pst;

   do
   {
	gotoxy(1,1);
	draw_check01(18, 18);
	display_stone(matrix);               //위치변경 
	gotoxy(x, y);
	printf("%s", stone[other]);          //위치변경 
	gotoxy(1, 20);
	printf("방향키로 움직이고 ");
	printf("스페이스 키를 누르시오.");
	gotoxy(1,21);
        printf("돌을 놓았으면 상대방 차례입니다. ");

	start=clock();                //시간체크 
	while(!kbhit())
	{
		end=clock();
		pst=(double)(end-start)/CLK_TCK;
		if (TIME_LIMIT<pst)
		{
			gotoxy(1, 21);
			printf("제한시간을 넘었습니다. \a");
			other=1-other;
			break;
		}
	}

	key=getch();
                                  //문제가 있음. 돌을 움직이는 과정에서도 시간을 체크해야 함.
	if (key==27)
		exit(0);
	else if (key>=72)
		move_arrow_key(key, &x, &y, 37, 19);
	else if(key==32)
	{
		if ((matrix[0][(x+1)/2][y]) || (matrix[1][(x+1)/2][y])) //그 위치에 돌이 있으면 못놓게 함
		{
			gotoxy(1,21);
			printf("이미 돌이 있습니다.              \a");
			continue;
		}
		else
		{
			matrix[other][(x+1)/2][y]=1;
			other=1-other;  //수정한 부분(획인)
		}
	}
   }while(1);
}

void display_stone(int matrix[][20][20])
{
	int i, x, y;
	char  *stone[2]={"○", "●"};

	for(i=0;i<2;i++)
		for(x=1;x<20;x++)
			for(y=1;y<20;y++)
			{
				if (matrix[i][x][y]==1)
				{
					gotoxy(x*2-1, y);
					printf("%s", stone[i]);
				}
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
		*x1=*x1-2;             //좌측방향으로 2씩 감소
		if (*x1<1)	*x1=1; //x좌표의 최소값
		break;
	case 77:  //오른쪽(우) 방향의 화살표 키 입력
		*x1=*x1+2;               //우측방향으로 2씩 증가
		if (*x1>x_b)  *x1=x_b; //x좌표의 최대값(경계)
		break;
	case 80:  //아래쪽(하) 방향의 화살표 키 입력
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y좌표의 최대값(경계)
		break;
	default:
		return;
	}
}

