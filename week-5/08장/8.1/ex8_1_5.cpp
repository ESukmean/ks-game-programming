#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);
void display_stone(int matrix[][20][20],int,int);

#define TIME_LIMIT 7

int Player;

int main(void)
{
    Player=0;
    game_control();
    return 0;
}


void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch(key)
    {
        case 72:  //위쪽(상) 방향의 화살표 키 입력 
            *y1=*y1-1;
            if (*y1<1) *y1=1;
            break;
        case 75:  //왼쪽(좌) 방향의 화살표 키 입력 
            *x1=*x1-2;
            if (*x1<1) *x1=1;
            break;
        case 77:  //오른쪽(우) 방향의 화살표 키 입력 
            *x1=*x1+2;
            if (*x1>x_b)  *x1=x_b;
            break;
        case 80:  //아래쪽(하) 방향의 화살표 키 입력 
            *y1=*y1+1;
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

int checkEnd(int m[2][20][20])
{
//검사 방법 
//배열의 처음 돌의 위치를 확인한 후 
//그 돌의 위치부터 수평수직대각선을 검사. 

    int x,y;
    for(x=1;x<=19-4;x++)
    {
        for(y=1;y<=19-4;y++)
            if(m[0][x][y]==1)
            {
                if((m[0][x][y+1]==1 && m[0][x][y+2]==1 &&
                    m[0][x][y+3]==1 && m[0][x][y+4]==1) ||
                   (m[0][x+1][y]==1 && m[0][x+2][y]==1 &&
                    m[0][x+3][y]==1 && m[0][x+4][y]==1) ||
                   (m[0][x+1][y+1]==1 && m[0][x+2][y+2]==1 &&
                    m[0][x+3][y+3]==1 && m[0][x+4][y+4]==1) ||
                   (m[0][x+1][y-1]==1 && m[0][x+2][y-2]==1 &&
                    m[0][x+3][y-3]==1 && m[0][x+4][y-4]==1))
                {
                    return 1; //흑돌승. 
                }

            }
            else if(m[1][x][y]==1)
            {
                if((m[1][x][y+1]==1 && m[1][x][y+2]==1 &&
                    m[1][x][y+3]==1 && m[1][x][y+4]==1) ||
                   (m[1][x+1][y]==1 && m[1][x+2][y]==1 &&
                    m[1][x+3][y]==1 && m[1][x+4][y]==1) ||
                   (m[1][x+1][y+1]==1 && m[1][x+2][y+2]==1 &&
                    m[1][x+3][y+3]==1 && m[1][x+4][y+4]==1) ||
                   (m[1][x+1][y-1]==1 && m[1][x+2][y-2]==1 &&
                    m[1][x+3][y-3]==1 && m[1][x+4][y-4]==1))
                {
                    return 2; //백돌승. 
                }

            }
    }
//matrix[0][(x+1)/2][y]); 
    return 0;
}

void game_control(void)
{
    int x=1, y=1, other=0,win;
    int matrix[2][20][20]={0};
    char key;
    char *stone[2]={"○","●"};
    clock_t start, end;
    double pst;
    do
    {
        again:
        gotoxy(1,1);
        draw_check01(18, 18);
        gotoxy(x, y);
        printf("%s", stone[other]);
        display_stone(matrix,x,y);
        //--------------------------------- 
        //새로 돌을 놓고 출력해 준 후에 
        //같은 돌 5개인지 확인 
        //리턴값이 1이면 1번 플레이어(흑돌) 승리 
        //리턴값이 2이면 2번 플레이어(백돌) 슬링 
        //리턴값이 0이면 계속 플레이. 
        win=checkEnd(matrix);
        if(1==win)
        {
            gotoxy(1, 22);
            printf("%d번 플레이어 승리",win);
            //game end; 
            return;
        }
        else if(2==win)
        {
            gotoxy(1, 22);
            printf("%d번 플레이어 승리",win);
            //game end; 
            return;
        }
        gotoxy(1, 23);
        //printf("x=%2d ,y=%2d  결과=%d    ",x,y,matrix[0][(x+1)/2][y]); 
        start=clock();
        gotoxy(1, 20);
        printf("방향키로 움직이고 ");
        printf("스페이스 키를 누르시오.ESC키는 게임 종료.");
        gotoxy(1,21);
        if(Player)
        {
            printf("백돌 차례입니다. ");
        }
        else
        {
            printf("흑돌 차례입니다. ");
        }
        //------------------------------------ 
        key=getch();
        if(key==27) return;//ESC 게임끝 
        else if (key>71)
            move_arrow_key(key, &x, &y, 37, 19);
        else if(key==32) //스페이스. 
        {
            end=clock();
            pst=(double)(end-start)/CLK_TCK;
            if (pst>TIME_LIMIT)
            {
                other=1-other;
                goto again;
            }
            if ((matrix[0][(x+1)/2][y]==1) || (matrix[1][(x+1)/2][y]==1))
            {
                gotoxy(1, 21);
                printf("돌을 놓지못함!"); 
                
                goto again;
            }
            else
            {
                matrix[other][(x+1)/2][y]=1;
                other=1-other;
                Player=(Player==0?1:0);
            }
        }
    }while(1);
}

void display_stone(int matrix[][20][20],int xx,int yy)
{
    int i, x, y;
    //돌 움직일때 모양 추가 
    char  *stone[3]={"○", "●","⊙"};

    for(i=0;i<2;i++)
        for(x=1;x<20;x++)
            for(y=1;y<20;y++)
            {
                //------------------------------- 
                if(x==((xx+1)/2) && y==yy)
                {
                    if(matrix[0][x][y]==0 && matrix[1][x][y]==0)
                    {
                        gotoxy(x*2-1, y);
                        printf("%s", stone[2]);
                    }
                }
                //------------------------------ 
                if (matrix[i][x][y]==1)
                {
                    gotoxy(x*2-1, y);
                    printf("%s", stone[i]);
                }
            }
}

