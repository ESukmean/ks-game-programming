#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void intro_game(void);
void game_control(void);
int user1_number(int i, int user1_array[]);
int user2_number(int i, int user2_array[]);
void number_display(int i, int user1_array[], int user2_array[], int sum);
void conclusion(int win);
void gotoxy(int x, int y);

int main(void)
{
	srand(time(NULL));
	intro_game();
	game_control();
	return 0;
}


void intro_game(void)
{
	system("cls");
	printf("100을 넘어라 게임\n\n");
	printf("두 사람이 번갈아가며\n");
	printf("숫자를 입력하되 1~10사이의 \n");
	printf("중복되지 않는 숫자를 입력하여 \n\n");
	printf("최초로 100을 넘기면 승자가 됩니다. \n\n");
	printf("아무키나 누르면 시작합니다.");
	getch();
}

int user1_number(int i, int user1_array[])
{
	int j, number;
	again:;
	gotoxy(1, 7);
	printf("                                 ");
	gotoxy(1, 7);
	printf("첫번째 사람 숫자 입력후 Enter>");
	scanf("%d", &number);
	for(j=0;j<i;j+=1)
		if (user1_array[j]==number)
		{
			gotoxy(1, 8);
			printf("중복된 숫자를 입력했습니다. \n");
			goto again;
		}
	gotoxy(1, 8);
	printf("                                      ");

	user1_array[i]=number;
	return user1_array[i];
}


int user2_number(int i, int user2_array[])
{
	int j, number;
	again:;
	gotoxy(1, 7);
	printf("                                 ");
	gotoxy(1, 7);
	printf("두번째 사람 숫자 입력후 Enter>");
	scanf("%d", &number);
	for(j=0;j<i;j+=1)
		if (user2_array[j]==number)
		{
			gotoxy(1, 8);
			printf("중복된 숫자를 입력했습니다. \n");
			goto again;
		}
	gotoxy(1, 8);
	printf("                                      ");
	user2_array[i]=number;
	return user2_array[i];
}

void number_display(int i, int user1_array[], int user2_array[], int sum)
{
	int j;
	gotoxy(1, 2);
	printf("첫번째 사람의 숫자 : ");
	for(j=0;j<=i;j+=1)
		if (user1_array[j]==0)
			continue;
		else
			printf("%2d ", user1_array[j]);

	gotoxy(1, 3);
	printf("두번째 사람의 숫자 : ");
	for(j=0;j<=i;j+=1)
		if (user2_array[j]==0)
			continue;
		else
			printf("%2d ", user2_array[j]);
	gotoxy(1, 5);
	printf("현재 합계 : %3d\n", sum);
}

void conclusion(int check)
{
	if (check==1)
		printf("컴퓨터가 이겼습니다. \n");
	else
		printf("사용자가 이겼습니다. \n");
}

void game_control(void)
{
	int max=100;
	int user1_array[10]={0}, user2_array[10]={0}, number;
	int i, sum=0, win; 
	system("cls");
	for(i=0;i<10;i+=1)
	{
		number=user1_number(i, user1_array);
		sum+=number;
		number_display(i, user1_array, user2_array, sum);
		if (max<sum)
		{
			win=1;
			break;
		}
		number=user2_number(i, user2_array);
		sum+=number;
		number_display(i, user1_array, user2_array, sum);
		if (max<sum)
		{
			win=2;
			break;
		}
	}
	conclusion(win);
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

