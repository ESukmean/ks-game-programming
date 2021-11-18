// 문자와 숫자가 동시에 나타나도록 제어
// 출현빈도가 가장 많이 나타난 숫자를 유일하게 나타나도록 난수를 반복 생성
// 난수에 의해 만들어진 숫자(0~9)가 5미만 이면 숫자(0,1,2,3,4), 5~9 범위면 문자(a,b,c,d,e)로 간주
 
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7    // 7*7 행렬
#define MAX_NUMBER 5     //숫자 범위 0~4, 문자범위 a~e

#define TIME_LIMIT 10    //제한시간 10초

void intro_game(void);
void game_control(void);
void print_number(int n, int cnt[]);
void adjust_print_number(int n, int cnt[]); //수정한 함수
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
	printf("정방행렬에 나타난 숫자와 문자 중에서\n");
	printf("가장 많이 출현한 것을 찾아라!\n\n");
	printf("제한시간은 %d초입니다.\n\n", TIME_LIMIT);
	printf("아무키나 누르면 시작합니다. \n");
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
	printf("출현횟수가 가장 많은 것은?(문자 또는 숫자입력>");
	start=clock();
	while(!kbhit())
	{
		end=clock();
		pst=(double)(end-start)/CLK_TCK;
		if (TIME_LIMIT<pst)
		{
			printf("\n제한시간을 넘었습니다. \n");
			if (answer<MAX_NUMBER)
				printf("정답은 %d이고 %d회 입니다.\n", answer, cnt[answer]);
			else
				printf("정답은 %c이고 %d회 입니다.\n", answer+92, cnt[answer]);
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
	int max_bin1, max_bin2; //출현빈도 최대값(max_num1)과 차순위 최대값(max_num2)을 계산
	int max_num;     //출현빈도가 가장 많이 나타난 것
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
	}while(max_bin1==max_bin2); //출현빈도의 최대값과 차순위 최대값이 같으면 다시 난수발생
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
			printf("\n맞았습니다. \n");
		else
			printf("\n틀렸습니다. \n");
		printf("번호: %d, 횟수 : %d\n", answer, cnt[answer]);  
	}
	else
	{
		if ((user-92)==answer)
			printf("\n맞았습니다. \n");
		else
			printf("\n틀렸습니다. \n");
		printf("문자: %c, 횟수 : %d\n", answer+92, cnt[answer]);  
	}
} 
