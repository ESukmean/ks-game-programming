// �������� �ִ밪�� �ּҰ��� �����ϰ� ��Ÿ�������� ���� �ݺ� ����
 
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#define MATRIX_SIZE 5
#define MAX_NUMBER 5
#define TIME_LIMIT 5   //���ѽð� 5�� 

void intro_game(void);
void game_control(void);
void print_number(int n, int cnt[]);
void adjust_print_number(int n, int cnt_max[], int cnt_min[]); //������ �Լ�

int find_max_num(int cnt_max[]); //������ �Լ�
int find_min_num(int cnt_min[]); //������ �Լ�

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
	printf("���� ����  ������ ���ڿ� \n");
	printf("���� ����  ������ ���ڸ� ã�ƶ�! \n\n");
	printf("���ѽð��� ���� 5���Դϴ�.\n\n");
	printf("�ƹ�Ű�� ������ �����մϴ�. \n");
	getch();
}

void game_control(void)
{
	int cnt_min[MAX_NUMBER], cnt_max[MAX_NUMBER], answer1, answer2, user1, user2;
	clock_t start, end;
	double pst;
	system("cls");
	adjust_print_number(MATRIX_SIZE, cnt_min, cnt_max);
	answer1=find_max_num(cnt_max);
	answer2=find_min_num(cnt_min);

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
			printf("������ %d�̰� %dȸ �Դϴ�.\n", answer1, cnt_max[answer1]);
			goto next;
		}
	}
	user1=getch()-'0';
	printf("%d", user1);
	check_result(user1, answer1, cnt_max);
	
	next:
	printf("����Ƚ���� ���� ���� ���� �Է�>");
	start=clock();
	while(!kbhit())
	{
		end=clock();
		pst=(double)(end-start)/CLK_TCK;
		if (TIME_LIMIT<pst)
		{
			printf("\n���ѽð��� �Ѿ����ϴ�. \n");
			printf("������ %d�̰� %dȸ �Դϴ�.\n", answer2, cnt_min[answer2]);
			exit(0);
		}
	}
	user2=getch()-'0';
	printf("%d", user2);
	check_result(user2, answer2, cnt_min);

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


void adjust_print_number(int n, int cnt_max[], int cnt_min[])
{
	int i, j, r_num[MATRIX_SIZE*MATRIX_SIZE];
	int num;
	int max_bin1, max_bin2; //������ �ִ밪(max_bin1)�� ������ �ִ밪(max_bin2)�� ���
	int max_num;     //�����󵵰� ���� ���� ��Ÿ�� ����(��)

	int min_bin1, min_bin2; //������ �ּҰ�(min_bin1)�� ������ �ּҰ�(min_bin2)�� ���
	int min_num;     //�����󵵰� ���� ���� ��Ÿ�� ����(��)

	
	int count;
	do
	{
		max_num=min_num=count=0;
		max_bin1=max_bin2=0;
		min_bin1=min_bin2=MATRIX_SIZE;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				r_num[count]=rand()%MAX_NUMBER;
				count+=1;
			}
		count=0;   //�������� �ִ밪 ���
		for(i=0;i<MAX_NUMBER;i+=1)
			cnt_max[i]=0;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				num=r_num[count];
				cnt_max[num]+=1;
				count+=1;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
			if (max_bin1<=cnt_max[i])
			{
				max_bin1=cnt_max[i];
				max_num=i;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
		{
			if (i==max_num)
				continue;
			else if (max_bin2<=cnt_max[i])
				max_bin2=cnt_max[i];
		}


		count=0; //�������� �ּҰ� ���
		for(i=0;i<MAX_NUMBER;i+=1)
			cnt_min[i]=0;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				num=r_num[count];
				cnt_min[num]+=1;
				count+=1;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
			if (min_bin1>=cnt_min[i])
			{
				min_bin1=cnt_min[i];
				min_num=i;
			}
		for(i=0;i<MAX_NUMBER;i+=1)
		{
			if (i==min_num)
				continue;
			else if (min_bin2>=cnt_min[i])
				min_bin2=cnt_min[i];
		}
	}while((min_bin1==min_bin2) || (max_bin1==max_bin2)); //�������� �ּҰ��� �ִ밪�� �������� ������ �ٽ� �����߻�
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

int find_max_num(int cnt_max[])
{
	int i, check, max_num=0;
	for(i=0;i<MAX_NUMBER;i+=1)
	{
		if (max_num<=cnt_max[i])
		{
			max_num=cnt_max[i];
			check=i;
		}
	}
	return check;
}


int find_min_num(int cnt_min[])
{
	int i, check, min_num=MATRIX_SIZE;
	for(i=0;i<MAX_NUMBER;i+=1)
	{
		if (min_num>=cnt_min[i])
		{
			min_num=cnt_min[i];
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
