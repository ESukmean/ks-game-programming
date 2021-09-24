#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define box_length 15 //게임의 영역(좌우 길이)
#define box_height 15 //바닥의 높이(상하 길이)
#define MAXCOUNT 20 //총시도 횟수

void intro_game(void);
int game_control(void);
void gotoxy(int x, int y);
int left_right_move(void);
void move_down(int x);
void draw_rectangle(int c, int r);
int max_block(void);

int block_stack[box_length*2+1]={0}; // 해당위치의 블록을 누적
static int a=0,b=0;
int main(void)
{
    int r;
    intro_game();
    r=game_control();
    gotoxy(1, box_height+3);
    if(r)printf("게임성공하셨습니다. \n");
    else printf("게임실패하였습니다. \n");
    printf("game이 종료되었습니다. ;                 \n");

    return 0;
}

void intro_game(void)
{
    system("cls");
    printf("----------------------------------------------------\n");
	printf("1. 블록쌓기 \n");
    printf("2. 블록이 좌우로 움직일때 스페이스키를 누르면\n");
    printf("3. 블록이 떨어져 바닥에 쌓입니다.\n");
    printf("4. 아무키나 누르면 게임을 시작합니다.\n");
	printf("5. 한턴에 한번씩 모양이 바낍니다.\n");
	printf("6. 20판이 되도록 밑에 한줄을 못쌓으시면 실패입니다.\n");
	printf("----------------------------------------------------\n");	
   getch();
}

int game_control(void)
{
    int x, count=0,i,sw;
    system("cls");
    draw_rectangle(box_length, box_height);
    gotoxy(box_length*2+5,3);
    printf("블록의 개수: %2d", box_height);
    gotoxy(1, box_height+3);
    printf("스페이스키를 누르면 블록이 떨어지고\n");
    printf("바닥에 쌓입니다. \n");

    //while(count<box_height)
    while(count<MAXCOUNT)
    {
        gotoxy(box_length*2+5,4);
        printf("시도한 횟수: %2d", count+1);
        gotoxy(box_length*2+5,5);
        printf("가장 많이 쌓인 블록수: %2d", max_block());
        for(i=3;i<=box_length*2+1;i+=2)
		{
            gotoxy(box_length*2+5+i-1,6);
            printf("%2d", block_stack[i]);
        }
        sw=1;
        for(i=3;i<=box_length*2+1;i+=2){
            if(block_stack[i]==0)//빈곳이 있으면
            {
              sw=0;
            }
        }

        if(sw)
        {
            return 1;
        }

        x=left_right_move();
        move_down(x);
        count++;
        getch();
    }
    return 0;
}

int max_block(void)
{
    int i, max=0;
    for(i=1;i<box_height*2+1;i++)
    {
        if (max<=block_stack[i])
        max=block_stack[i];
    }
    return max;
}


int left_right_move(void)
{
    int x=3, y=2, temp=2;
	if(b==0)
	{
		a=0;
		b=1;
	}
	else
	{
		a=1;
		b=0;
	}
    do
    {
        x+=temp;
        if (x>(box_length*2)) //x방향 최대값 설정
        temp=-2;
        if (x<3)
        {
            x=3;
            temp=2;
        }
		if(a==0)
		{
			gotoxy(x, y);
			printf("●");
		}
		else
		{
			gotoxy(x, y);
			printf("★");
		}
        Sleep(50); //블록이 좌우로 움직이는 속도를 조절
        gotoxy(x, y);
        printf("  ");
    }while(!kbhit());
    block_stack[x]+=1;
    return x;
}

void move_down(int x)
{
    int y;
    for(y=2;y<box_height+2-block_stack[x];y+=1)
    {
		if(a==0)
		{
			gotoxy(x, y);
			printf("●");
		}
		else
		{
			gotoxy(x, y);
			printf("★");
		}
        Sleep(20);
        gotoxy(x, y);
        printf("  ");
        Sleep(10);
    }
    gotoxy(x,box_height+2-block_stack[x]);
    if(a==0)
	{
		printf("●");
	}
	else
	{
		printf("★");
	}
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_rectangle(int r, int c)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7];

    for(i=1;i<7;i++)
        b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<r;i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");

    for(i=0;i<c;i++)
    {
        printf("%c%c", a, b[2]);
        for(j=0;j<r;j++)
        printf("  ");
        printf("%c%c",a, b[2]);
        printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<r;i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}