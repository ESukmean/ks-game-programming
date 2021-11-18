//�ذ����� 2���� ���ٹ���� �̿��� �� �ִ�.
// [��� 1]�� �������� �ִ밪�� �����ϰ� ����
// [��� 2]�� �ִ�󵵰� �������� ���� ��� �ߺ����� ���� ����
// [��� 1] : �����󵵰� ���� ���� ��Ÿ�� ���ڸ� �����ϰ� ��Ÿ������ ������ �ݺ� ����
 
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#define MATRIX_SIZE 5
#define MAX_NUMBER 5
#define TIME_LIMIT 5

void intro_game(void);
void game_control(void);
void print_number(int n, int cnt[]);
void adjust_print_number(int n, int cnt[]); //������ �Լ�
int find_num(int cnt[]);
void check_result(int user, int answer, int cnt[]);

int main(void)
{
	srand(time(NULL));
	intro_game();
    	game_control();
	return 0;
}


void intro_game(void)
{
	printf("������Ŀ� ��Ÿ�� ���� �߿���\n");
	printf("���� ���� ������ ���ڸ� ã�ƶ�!\n\n");
	printf("���ѽð��� 5���Դϴ�.\n\n");
	printf("�ƹ�Ű�� ������ �����մϴ�. \n");
	getch();
}

void game_control(void)
{
	int cnt[MAX_NUMBER], answer, user;
	clock_t start, end;
	double pst;
	system("cls");
	adjust_print_number(MATRIX_SIZE, cnt);
	answer=find_num(cnt);
	printf("\n\n");
	printf("����Ƚ���� ���� ���� ���� �Է�>");
	start=clock();
	while(!kbhit())
	{
		end=clock();
		pst=(double)(end-start)/CLK_TCK;
		if (TIME_LIMIT<pst)
		{
			printf("\n���ѽð��� �Ѿ����ϴ�. \n");
			printf("������ %d�̰� %dȸ �Դϴ�.\n", answer, cnt[answer]);
			exit(0);
		}
	}
	user=getch()-'0';
	printf("%d", user);
	check_result(user, answer, cnt);
}

void print_number(int n, int cnt[])
{
	int i, j, r_num;
	for(i=0;i<MAX_NUMBER;i+=1)
		cnt[i]=0;
	for(i=1;i<=n;i+=1)
	{
		for(j=1;j<=n;j+=1)
		{
			r_num=rand()%MAX_NUMBER;
			cnt[r_num]+=1;
			printf("%d ", r_num);
		}
		printf("\n");
	}
}


void adjust_print_number(int n, int cnt[])
{
	int i, j, r_num[MATRIX_SIZE*MATRIX_SIZE];
	int num;
	int max_bin1, max_bin2; //������ �ִ밪(max_num1)�� ������ �ִ밪(max_num2)�� ���
	int max_num;     //�����󵵰� ���� ���� ��Ÿ�� ����
	int count;
	do
	{
		max_num=count=max_bin1=max_bin2=0;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				r_num[count]=rand()%MAX_NUMBER;
				count+=1;
			}
		count=0;
		for(i=0;i<MAX_NUMBER;i+=1)
			cnt[i]=0;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				num=r_num[count];
				cnt[num]+=1;
				count+=1;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
			if (max_bin1<=cnt[i])
			{
				max_bin1=cnt[i];
				max_num=i;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
		{
			if (i==max_num)
				continue;
			else if (max_bin2<=cnt[i])
				max_bin2=cnt[i];
		}
	}while(max_bin1==max_bin2); //�������� �ִ밪�� ������ �ִ밪�� ������ �ٽ� �����߻�
	count=0;
	for(i=1;i<=n;i+=1)
	{
		for(j=1;j<=n;j+=1)
		{
			printf("%d ", r_num[count]);
			count+=1;
		}
		printf("\n");
	}
}

int find_num(int cnt[])
{
	int i, check, max_num=0;
	for(i=0;i<MAX_NUMBER;i+=1)
	{
		if (max_num<=cnt[i])
		{
			max_num=cnt[i];
			check=i;
		}
	}
	return check;
}


void check_result(int user, int answer, int cnt[])
{
	if (user==answer)
		printf("\n�¾ҽ��ϴ�. \n");
	else
		printf("\nƲ�Ƚ��ϴ�. \n");
	printf("��ȣ: %d, Ƚ�� : %d\n", answer, cnt[answer]);
}
