#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void display_rule(void);
void draw_check02(int c, int r);
void reel_series(int r[][3]);
void gotoxy(int x, int y);
int game_progress(int money);
void display_reel(char rc[][3], int r[][3], int index);
void clear_text(void);
void game_control(char reel[][3], int reel_num[][3], int *money);
int  return_money(int r[], int betting, int *case_n);

int main(void)
{
	char reel[6][3]={"★", "♠", "◆", "♥", "♣", "○"};
	int  i, reel_num[3][3];
	int money=10000;
	srand(time(NULL));
	printf("  슬롯머신 게임\n\n");
	display_rule();
	gotoxy(3, 5);
	printf("릴1 릴2 릴3");
	gotoxy(1,6);
	draw_check02(3, 3);
	for(i=0;i<3;i++)
		reel_num[0][i]=rand()%5;
	reel_series(reel_num);
	
	do
	{
		game_control(reel, reel_num, &money);
	}while(money);
	gotoxy(3,20);
	return 0;
}
void display_rule(void)
{
	gotoxy(30, 3); 
	printf("   릴1   릴2  릴3  사례금\n"); 
	gotoxy(30, 4); 
	printf("--------------------------\n");
	gotoxy(30, 5); 
	printf(" 1: ★   ★   ★\t*10\n"); 
	gotoxy(30, 6); 
	printf(" 2: ♠   ♠   ♠\t *7\n"); 
	gotoxy(30, 7); 
	printf(" 3: ◆   ◆   ◆\t *5\n"); 
	gotoxy(30, 8); 
	printf(" 4: ★   ★   기타\t *4\n"); 
	gotoxy(30, 9); 
	printf(" 5: ♠   ♠   기타\t *3\n"); 
	gotoxy(30, 10); 
	printf(" 6: ◆   ◆   기타\t *3\n"); 
	gotoxy(30, 11); 
	printf(" 7: ♥   ♥   기타\t *3\n"); 
	gotoxy(30, 12); 
	printf(" 8: ♣   ♣   기타\t *2\n"); 
	gotoxy(30, 13); 
	printf(" 9: ○   ○   기타\t *1\n"); 

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

void reel_series(int r[][3])
{
	int i, j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			r[j][i]=(r[0][i]+j)%6;

}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int game_progress(int money)
{
    int bet;
	gotoxy(43, 17);
	printf("현재 남은 금액 : %d원", money);
	gotoxy(1, 17);
	printf("배팅금액을 입력하고 Enter키를 누르면 ");
	gotoxy(1, 19);
	printf("0을 입력하면 종료합니다.");
	gotoxy(1, 18);
	printf("게임을 시작합니다. 금액 입력>");
	gotoxy(30, 18);
	scanf("%d", &bet);
	if (bet==0)
		exit(0);
	gotoxy(1, 19);
	printf("아무키나 한번만 키를 누르면 릴이 멈춥니다.");
	return bet;

}
void display_reel(char rc[][3], int r[][3], int index)
{
	int i, j;
	for(i=0;i<3;i++)
		for(j=index;j<3;j++)
		{
			gotoxy(3+j*4, 7+i*2);
			printf("%s", rc[r[i][j]]);
		}

}

void clear_text(void)
{
	int i, j;
	for(i=17;i<20;i++)
	{
		gotoxy(1, i);
		for(j=0;j<42;j++)
			printf(" ");
	}

}
void game_control(char reel[][3], int reel_num[][3], int *money)
{
	int i, j, bet, case_num=0, thank, num[3];
	double pst;
	clock_t start, end;

	display_reel(reel, reel_num, 0);
	bet=game_progress(*money);

	for(i=0;i<3;i++)
	{
		start=clock();
		do
		{
			for(j=i;j<3;j++)
				reel_num[0][j]=reel_num[1][j];
			reel_series(reel_num);		
			display_reel(reel, reel_num, i);
			end=clock();
			pst=(double)(end-start)/CLK_TCK;
		}while(!kbhit() || (pst<1));
		num[i]=reel_num[1][i];
	}
	getch();
	thank=return_money(num, bet, &case_num);
	if (thank==0)
		*money-=bet;
	else
		*money+=thank;
	if (case_num)
	{
	  gotoxy(43, 18);
	  printf("사례:%d, 배팅:%d원, 사례금:%d", case_num, bet, thank);
	}
	clear_text();

}
int  return_money(int r[], int betting, int *case_num)
{
	int total=0;
	if (r[0]==r[1] && r[1]==r[2]  && r[0]==r[2])
	{
		if (r[0]==0)
		{
			total=betting*10;
			*case_num=1;
		}
		else if (r[0]==1)
		{
			total=betting*7;
			*case_num=2;
		}
		else if (r[0]==2)
		{
			total=betting*5;
			*case_num=3;
		}
	}
	else if((r[0]==0 && r[1]==0) || (r[1]==0 && r[2]==0) || 		   (r[0]==0 && r[2]==0))
	{
		total=betting*4;
		*case_num=4;
	}
	else if( (r[0]==1 && r[1]==1) || (r[1]==1 && r[2]==1 ) || 		   (r[0]==1 && r[2]==1))
	{
		total=betting*3;
		*case_num=5;
	}
	else if( (r[0]==2 && r[1]==2) || (r[1]==2 && r[2]==2 ) || 		   (r[0]==2 && r[2]==2))
	{
		total=betting*3;
		*case_num=6;
	}
	else if( (r[0]==3 && r[1]==3) || (r[1]==3 && r[2]==3 ) || 		   (r[0]==3 && r[2]==3))
	{
		total=betting*3;
		*case_num=7;
	}
	else if( (r[0]==4 && r[1]==4) || (r[1]==4 && r[2]==4 ) || 		   (r[0]==4 && r[2]==4))
	{
		total=betting*2;
		*case_num=8;
	}
	else if( (r[0]==5 && r[1]==5) || (r[1]==5 && r[2]==5 ) || 		   (r[0]==5 && r[2]==5))
	{
		total=betting*1;
		*case_num=9;
	}
	return total;
}
