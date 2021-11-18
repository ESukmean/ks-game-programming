// ���ڿ� ���ڰ� ���ÿ� ��Ÿ������ ����
// �����󵵰� ���� ���� ��Ÿ�� ���ڸ� �����ϰ� ��Ÿ������ ������ �ݺ� ����
// ������ ���� ������� ����(0~9)�� 5�̸� �̸� ����(0,1,2,3,4), 5~9 ������ ����(a,b,c,d,e)�� ����
 
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7    // 7*7 ���
#define MAX_NUMBER 5     //���� ���� 0~4, ���ڹ��� a~e

#define TIME_LIMIT 10    //���ѽð� 10��

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
	printf("������Ŀ� ��Ÿ�� ���ڿ� ���� �߿���\n");
	printf("���� ���� ������ ���� ã�ƶ�!\n\n");
	printf("���ѽð��� %d���Դϴ�.\n\n", TIME_LIMIT);
	printf("�ƹ�Ű�� ������ �����մϴ�. \n");
	getch();
}

void game_control(void)
{
	int cnt[MAX_NUMBER*2], answer, user;
	clock_t start, end;
	double pst;
	system("cls");
	adjust_print_number(MATRIX_SIZE, cnt);
	answer=find_num(cnt);
	printf("\n\n");
	printf("����Ƚ���� ���� ���� ����?(���� �Ǵ� �����Է�>");
	start=clock();
	while(!kbhit())
	{
		end=clock();
		pst=(double)(end-start)/CLK_TCK;
		if (TIME_LIMIT<pst)
		{
			printf("\n���ѽð��� �Ѿ����ϴ�. \n");
			if (answer<MAX_NUMBER)
				printf("������ %d�̰� %dȸ �Դϴ�.\n", answer, cnt[answer]);
			else
				printf("������ %c�̰� %dȸ �Դϴ�.\n", answer+92, cnt[answer]);
			exit(0);
		}
	}
	user=getch()-'0';
	if (user<MAX_NUMBER)
		printf("%d", user);
	else
	{
		user+=48;
		printf("%c", user);
	}
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
	int max_num;     //�����󵵰� ���� ���� ��Ÿ�� ��
	int count;
	do
	{
		max_num=count=max_bin1=max_bin2=0;
		for(i=1;i<=n;i+=1)
			for(j=1;j<=n;j+=1)
			{
				r_num[count]=rand()%(MAX_NUMBER*2);
				count+=1;
			}

		count=0;
		for(i=0;i<(MAX_NUMBER*2);i+=1)
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
			if (r_num[count]<MAX_NUMBER)
				printf("%d ", r_num[count]);
			else
				printf("%c ", r_num[count]+92);
			count+=1;
		}
		printf("\n");
	}
}

int find_num(int cnt[])
{
	int i, check, max_num=0;
	for(i=0;i<(MAX_NUMBER*2);i+=1)
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
	if (user<MAX_NUMBER)
	{
		if (user==answer)
			printf("\n�¾ҽ��ϴ�. \n");
		else
			printf("\nƲ�Ƚ��ϴ�. \n");
		printf("��ȣ: %d, Ƚ�� : %d\n", answer, cnt[answer]);  
	}
	else
	{
		if ((user-92)==answer)
			printf("\n�¾ҽ��ϴ�. \n");
		else
			printf("\nƲ�Ƚ��ϴ�. \n");
		printf("����: %c, Ƚ�� : %d\n", answer+92, cnt[answer]);  
	}
} 
