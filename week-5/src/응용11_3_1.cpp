#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

int intro_game(void);
void draw_check02(int r, int c);
void gotoxy(int x, int y);
void number_display(int n);
void display_rule(int n, char question[][10]);
void make_question(int n, char question[][10]);
void game_control(char question[][10], int n, int *count);
void clear_text(void);

int main(void)
{
	int n, count=0;
	char question[10][10]={0};
	char answer[10][10]={0};
	long pst, seconds, minutes;
	clock_t start, end;

	srand(time(NULL));
	n=intro_game();
	system("cls");
	draw_check02(n, n);
	number_display(n);
	display_rule(n, question);
	number_display(n);
	start=clock();
	do
	{
		game_control(question, n, &count);
	}while(count<n*n/2);
	gotoxy(2, 18);
	printf("모두 맞았습니다. 종료합니다. \n");
	end=clock();
	pst=(end-start)/CLK_TCK;
	minutes=pst/60;
	seconds=pst-minutes*60;
	gotoxy(2, 19);
	printf("경과시간 : %ld분 %ld 초\n", minutes, seconds);
	return 0;
}

int intro_game(void)
{
 //[함수 11.3.1]의 정의 부분 참고
	int n;
	system("cls");
	printf("문자 퍼즐 맞추기 \n\n");
	printf("격자모양의 판에 숨겨진 두 개의 문자를 찾는 \n");
	printf("게임입니다. \n\n");
	printf("행의 숫자(4 또는 6)를 입력하고 Enter>");
	scanf("%d",&n);
	return n;
}
void display_rule(int n, char question[][10])
{
 //[함수 11.3.2]의 정의 부분 참고
	gotoxy(2,14);
	printf("위와 같은 격자모양의 숫자 뒤에는 \n");
	gotoxy(2,15);
	printf("같은 모양의 문자가 두개씩 숨어 있습니다. \n");
	gotoxy(2,16);
	printf("아무키나 누르면 정답화면이 잠시 나타납니다. \n");
	getch();
	clear_text();
	make_question(n, question);
	gotoxy(2,14);
	printf("정답화면은 위와 같습니다. \n");
	gotoxy(2,15);
	printf("5초 뒤에 문제 풀이를 시작합니다. \n");
	Sleep(5000);
	clear_text();
}
void game_control(char question[][10], int n, int *count)
{
 //[함수 11.3.3]의 정의 부분 참고
	int user1, user2, row1, row2, col1, col2;
	gotoxy(2, 14);
	printf("첫번째 숫자를 입력하고 Enter>");
	scanf("%d", &user1);
	row1=user1/n;
        col1=user1%n;
	gotoxy(2, 15);
	printf("두번째 숫자를 입력하고 Enter>");
	scanf("%d", &user2);
	row2=user2/n;
	col2=user2%n;
	if (question[row1][col1]==question[row2][col2])
	{
		  *count=*count+1;
		  gotoxy(28, 4);
		  printf("맞은 개수:%2d개(총 %2d개)", *count, n*2);
		  gotoxy(3+4*col1, 2+2*row1);
		  printf("%2c", question[row1][col1]);
		  gotoxy(3+4*col2, 2+2*row2);
		  printf("%2c", question[row2][col2]);
	  	  gotoxy(2, 16);
	      printf("맞았습니다. 아무키나 누르면 다시 시작합니다. ");
  		  getch();
		  clear_text();
	}
	else
	{
		  gotoxy(3+4*col1, 2+2*row1);
		  printf("%2c", question[row1][col1]);
		  gotoxy(3+4*col2, 2+2*row2);
		  printf("%2c", question[row2][col2]);
		  Sleep(3000);
		  gotoxy(3+4*col1, 2+2*row1);
		  printf("%2d", user1);
		  gotoxy(3+4*col2, 2+2*row2);
		  printf("%2d", user2);
  	  	  gotoxy(2, 16);
	          printf("틀렸습니다. 아무키나 누르면 시작합니다. ");
		  getch();
		  clear_text();
	}
}
void clear_text(void)
{
 //[함수 11.3.4]의 정의 부분 참고
	int i, j;
	for(i=14;i<17;i++)
	{
		gotoxy(2, i);
		for(j=0;j<50;j++)
			printf(" ");
	}
}
void number_display(int n)
{
 //[함수 11.3.5]의 정의 부분 참고
  int i, j, count=0;
  for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	  {
		  gotoxy(3+4*j, 2+2*i);
		  printf("%2d", count);
		  count++;
	  }
}
void make_question(int n, char question[][10])
{
 //[함수 11.3.6]의 정의 부분 참고
  int number, i, j, ran, count1=0, count2=0;
  char chr1[26], chr2[26], temp;
  srand(time(NULL));
  number=n*n/2;
  for(i=0;i<26;i++)   {
	  chr1[i]=65+i;
	  chr2[i]=i;
  }
  for(i=0;i<number;i++)   {
	  ran=rand()%number;
	  temp=chr1[i];
	  chr1[i]=chr1[ran];
	  chr1[ran]=temp;
  }
  for(i=0;i<number;i++)   {
	  ran=rand()%number;
	  temp=chr2[i];
	  chr2[i]=chr2[ran];
	  chr2[ran]=temp;
  }
   for(i=0;i<n;i++)
	   for(j=0;j<n;j++) 	   {
		   if (count1<number)    {
				question[i][j]=chr1[count1];
				count1++;
		   }
		   else    {
			   question[i][j]=chr1[chr2[count2]];
			   count2++;
		   }
	   }
   for(i=0;i<n;i++)    {
	   for(j=0;j<n;j++) 	   {
		  gotoxy(3+4*j, 2+2*i);
		  printf("%2c", question[i][j]);
		 }
          }
}
void draw_check02(int r, int c)
{
 //[함수 3.5.4]의 정의 부분 참고
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
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
