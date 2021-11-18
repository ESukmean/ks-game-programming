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
        case 72:  //����(��) ������ ȭ��ǥ Ű �Է� 
            *y1=*y1-1;
            if (*y1<1) *y1=1;
            break;
        case 75:  //����(��) ������ ȭ��ǥ Ű �Է� 
            *x1=*x1-2;
            if (*x1<1) *x1=1;
            break;
        case 77:  //������(��) ������ ȭ��ǥ Ű �Է� 
            *x1=*x1+2;
            if (*x1>x_b)  *x1=x_b;
            break;
        case 80:  //�Ʒ���(��) ������ ȭ��ǥ Ű �Է� 
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
//�˻� ��� 
//�迭�� ó�� ���� ��ġ�� Ȯ���� �� 
//�� ���� ��ġ���� ��������밢���� �˻�. 

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
                    return 1; //�浹��. 
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
                    return 2; //�鵹��. 
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
    char *stone[2]={"��","��"};
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
        //���� ���� ���� ����� �� �Ŀ� 
        //���� �� 5������ Ȯ�� 
        //���ϰ��� 1�̸� 1�� �÷��̾�(�浹) �¸� 
        //���ϰ��� 2�̸� 2�� �÷��̾�(�鵹) ���� 
        //���ϰ��� 0�̸� ��� �÷���. 
        win=checkEnd(matrix);
        if(1==win)
        {
            gotoxy(1, 22);
            printf("%d�� �÷��̾� �¸�",win);
            //game end; 
            return;
        }
        else if(2==win)
        {
            gotoxy(1, 22);
            printf("%d�� �÷��̾� �¸�",win);
            //game end; 
            return;
        }
        gotoxy(1, 23);
        //printf("x=%2d ,y=%2d  ���=%d    ",x,y,matrix[0][(x+1)/2][y]); 
        start=clock();
        gotoxy(1, 20);
        printf("����Ű�� �����̰� ");
        printf("�����̽� Ű�� �����ÿ�.ESCŰ�� ���� ����.");
        gotoxy(1,21);
        if(Player)
        {
            printf("�鵹 �����Դϴ�. ");
        }
        else
        {
            printf("�浹 �����Դϴ�. ");
        }
        //------------------------------------ 
        key=getch();
        if(key==27) return;//ESC ���ӳ� 
        else if (key>71)
            move_arrow_key(key, &x, &y, 37, 19);
        else if(key==32) //�����̽�. 
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
                printf("���� ��������!"); 
                
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
    //�� �����϶� ��� �߰� 
    char  *stone[3]={"��", "��","��"};

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

