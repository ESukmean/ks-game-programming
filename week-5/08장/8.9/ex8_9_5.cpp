#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void display_race(int score[], char user[][3]);
void clear_text(void);
void press_any_key(void);
void game_control(int score[], char user[][3], int *win, int *max);
void gotoxy(int x, int y);

char user[4][3]={"♠", "◆", "♥", "♣"};
char user_name[4][7];
int  order[4]={0, 1, 2, 3}, trap[3], map[35]={0};   //trap 은 함정
int  user_number;

int main(void)
{
	int i, temp, ran, max=0;
	int score[4]={0}, win;

	srand(time(NULL));

	printf("함정이 있는 주사위 게임 \n\n");
	printf("게임에 참가할 인원수(최대 4) 입력 후 Enter>");
	scanf("%d", &user_number);
	printf("게임 순서는 무작위로 선정합니다. \n");

	for(i=0;i<user_number;i++)
	{
		printf("%d번 이름을 입력하고 Enter>", i+1);
		scanf("%s", &user_name[i]);
	}
	
	for(i=0; i<user_number; i++)
	{
		ran = rand()%user_number; 
		temp=order[i];
		order[i]=order[ran];
		order[ran]=temp;
	}

	for(i=0;i<3;i++)
			trap[i]=rand()%9+5+10*i;

	for(i=0;i<35;i++)
		map[i]=1;

	for(i=0;i<3;i++)
		map[trap[i]-1]=0;

	system("cls");
	gotoxy(1,1);
	printf("게임 순서는 다음과 같습니다. 괄호는 말기호\n");
	gotoxy(1,2);
	for(i=0;i<user_number;i++)
		printf("%d번:%s(%s) ", i+1, user_name[order[i]], user[order[i]]);
	gotoxy(1, 4);
	printf("□:함정, 위치 :");
	for(i=0;i<3;i++)
		printf("%2d ", trap[i]);

	display_race(score, user);

	do
	{
		game_control(score, user, &win, &max);
	}while(max<34);
	gotoxy(1, 14);
	printf("우승자는 %s님입니다. \n", user_name[win]);
	return 0;
}


void game_control(int score[], char user[][3], int *win, int *max)
{				  
	int i, j, ran;

	for(i=0;i<user_number;i++)
		{
			clear_text();
			gotoxy(1, 10);
			printf("%s님(현위치 %d) 할 차례. 아무키나 누르세요.", user_name[order[i]], score[order[i]]);
			getch();

			ran=rand()%6+1;
			score[order[i]]+=ran;
			gotoxy(1, 11);
			printf("주사위 눈금은 %d입니다. 이동할 위치:%d", ran, score[order[i]]);

			for(j=0;j<user_number;j++)
			{
				if (j==i)
					continue;
				else if (score[order[i]]==score[order[j]])
				{
					gotoxy(1,12);
					printf("%d번 말이 %d번 말을 잡았습니다.", i+1, j+1);
					score[order[j]]=0;
				}
			}
			for(j=0;j<3;j++)
				if (score[order[i]]==trap[j])
				{
					gotoxy(1,12);
					printf("%d번 말이 함정에 빠졌습니다.", order[i]+1);
					score[order[i]]=0;
				}
			if (score[order[i]]>35)
			{
				score[order[i]]=35;
				*max=35;
				*win=order[i];
				break;
			}
			display_race(score, user);
			gotoxy(1, 13);
			press_any_key();			
		}
}


void clear_text(void)
{
	int i, j;
	for(i=11;i<14;i++)
	{
		gotoxy(1, i);
		for(j=0;j<50;j++)
			printf(" ");
	}
}


void display_race(int score[], char user[][3])
{
	int i, x;

	gotoxy(1,6);
	printf("시작");
	gotoxy(69,6);
	printf("끝");

	gotoxy(1,7);
	for(i=0;i<35;i++)
	{
		if (map[i]==1)
			printf("■");
		else 
			printf("□");
	}
	gotoxy(1,8);
	for(i=0;i<75;i++)
		printf(" ");

	for(i=0;i<user_number;i++)
	{
		x=score[order[i]];
		if (x==0)
			continue;
		else
		{
			gotoxy(x*2-1, 8);
			printf("%s", user[order[i]]);
		}
	}
}


void press_any_key(void)
{
	printf("아무키나 누르면 다음 순서로 ...");
	getch();
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


