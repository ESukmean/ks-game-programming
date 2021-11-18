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

char user[4][3]={"��", "��", "��", "��"};
char user_name[4][7];
int  order[4]={0, 1, 2, 3}, trap[3], map[35]={0};   //trap �� ����
int  user_number;

int main(void)
{
	int i, temp, ran, max=0;
	int score[4]={0}, win;

	srand(time(NULL));

	printf("������ �ִ� �ֻ��� ���� \n\n");
	printf("���ӿ� ������ �ο���(�ִ� 4) �Է� �� Enter>");
	scanf("%d", &user_number);
	printf("���� ������ �������� �����մϴ�. \n");

	for(i=0;i<user_number;i++)
	{
		printf("%d�� �̸��� �Է��ϰ� Enter>", i+1);
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
	printf("���� ������ ������ �����ϴ�. ��ȣ�� ����ȣ\n");
	gotoxy(1,2);
	for(i=0;i<user_number;i++)
		printf("%d��:%s(%s) ", i+1, user_name[order[i]], user[order[i]]);
	gotoxy(1, 4);
	printf("��:����, ��ġ :");
	for(i=0;i<3;i++)
		printf("%2d ", trap[i]);

	display_race(score, user);

	do
	{
		game_control(score, user, &win, &max);
	}while(max<34);
	gotoxy(1, 14);
	printf("����ڴ� %s���Դϴ�. \n", user_name[win]);
	return 0;
}


void game_control(int score[], char user[][3], int *win, int *max)
{				  
	int i, j, ran;

	for(i=0;i<user_number;i++)
		{
			clear_text();
			gotoxy(1, 10);
			printf("%s��(����ġ %d) �� ����. �ƹ�Ű�� ��������.", user_name[order[i]], score[order[i]]);
			getch();

			ran=rand()%6+1;
			score[order[i]]+=ran;
			gotoxy(1, 11);
			printf("�ֻ��� ������ %d�Դϴ�. �̵��� ��ġ:%d", ran, score[order[i]]);

			for(j=0;j<user_number;j++)
			{
				if (j==i)
					continue;
				else if (score[order[i]]==score[order[j]])
				{
					gotoxy(1,12);
					printf("%d�� ���� %d�� ���� ��ҽ��ϴ�.", i+1, j+1);
					score[order[j]]=0;
				}
			}
			for(j=0;j<3;j++)
				if (score[order[i]]==trap[j])
				{
					gotoxy(1,12);
					printf("%d�� ���� ������ �������ϴ�.", order[i]+1);
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
	printf("����");
	gotoxy(69,6);
	printf("��");

	gotoxy(1,7);
	for(i=0;i<35;i++)
	{
		if (map[i]==1)
			printf("��");
		else 
			printf("��");
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
	printf("�ƹ�Ű�� ������ ���� ������ ...");
	getch();
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


