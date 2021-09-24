//��ǻ�Ͱ� �Է��� ���� ����ڰ� �Է��� ���� �ϳ��� �迭(num_array)�� �����Ͽ� check

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void intro_game(void);
void game_control(void);
int computer_number(int i, int num_array[]);
int user_number(int i, int num_array[]);
void number_display(int i, int num_array[], int sum);
void conclusion(int win);
void gotoxy(int x, int y);
void press_any_key(void);

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
	printf("50�� �Ѿ�� ����\n\n");
	printf("��ǻ�Ϳ� ����ڰ� �����ư���\n");
	printf("���ڸ� �Է��ϵ� 1~10������ \n");
	printf("���� �ߺ����� �ʴ� ���ڸ� �Է��Ͽ� \n\n");
	printf("���ʷ� 50�� �ѱ�� ���ڰ� �˴ϴ�. \n\n");
	printf("��ǻ�Ͱ� ���� �����մϴ�. \n");
	printf("�ƹ�Ű�� ������ �����մϴ�.");
	getch();
}

int computer_number(int i, int num_array[])
{
	int j, number;
	again:;
	number=rand()%10+1;
	for(j=0;j<=i;j+=1)
		if (num_array[j]==number)
			goto again;
	num_array[i]=number;
	return num_array[i];
}

int user_number(int i, int num_array[])
{
	int j, number;
	again:;
	gotoxy(1, 7);
	printf("����� ���� �Է��� Enter>");
	scanf("%d", &number);
	for(j=0;j<=i;j+=1)
		if (num_array[j]==number)
		{
			gotoxy(1, 8);
			printf("�ߺ��� ���ڸ� �Է��߽��ϴ�. \n");
			goto again;
		}
	num_array[i]=number;
	return num_array[i];
}

void number_display(int i, int num_array[], int sum)
{
	int j;
	gotoxy(1, 2);
	printf("��ǻ�� ���� : ");
	for(j=0;j<=i;j+=2)
		printf("%2d ", num_array[j]);
	gotoxy(1, 3);
	printf("����� ���� : ");
	for(j=1;j<=i;j+=2)
		if (num_array[j]==0)
			continue;
		else
			printf("%2d ", num_array[j]);
	gotoxy(1, 5);
	printf("���� �հ� : %3d\n", sum);
}

void conclusion(int check)
{
	if (check==1)
		printf("��ǻ�Ͱ� �̰���ϴ�. \n");
	else
		printf("����ڰ� �̰���ϴ�. \n");
}

void press_any_key(void)
{
	gotoxy(1, 10);
	printf("�ƹ�Ű�� �����ÿ�..");
	getch();
}

void game_control(void)
{
	int max=50; //�հ��� �ִ밪�� 50
	int num_array[10]={0}, number;
	int i=0, sum=0, win; 
	do
	{
		//�迭÷�� i�� ¦���� ��� : computer�� ������ ����
		//�迭÷�� i�� Ȧ���� ��� : ����ڰ� �Է��� ����
		system("cls");
		number=computer_number(i, num_array);
		sum+=number;
		number_display(i, num_array, sum);
		if (max<sum)
		{
			win=1;
			break;
		}
		i+=1;
		number=user_number(i, num_array);
		sum+=number;
		number_display(i, num_array, sum);
		if (max<sum)
		{
			win=2;
			break;
		}
		i+=1;
		press_any_key();
	}while(sum<max);
	conclusion(win);
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

