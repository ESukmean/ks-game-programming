#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void draw_check_pattern(int r, int c);
void gotoxy(int x, int y);
void char_display(char chr_set[]);
void display_rule(void);
void game_control(double time_limit);
int select_num(void);


int main(void)
{
    double time_limit;
	srand(time(NULL));
	do
	{
		system("cls");
		display_rule();
		time_limit=50-select_num()*10L;
		printf("\n�ƹ�Ű�� ������ ������ �����մϴ�. ");
		getch();
		game_control(time_limit);
	}while(1);
	return 0;
}

void game_control(double time_limit)
{
	char chr[2]={'b', 'd'};
	char chr_set[36], temp;
	int i, count=0, number, yes;
	int rand1, rand2, rand3;
	double pst;

	time_t start, end;
	rand1=rand()%2;
	rand2=rand()%6;
	if (rand1)
		rand2=18+rand2;
	else
		rand2=18-rand2;
	for(i=0;i<rand2;i++)
	    chr_set[i]=chr[rand1];
	for(i=rand2;i<36;i++)
	    chr_set[i]=chr[1-rand1];
	
	for(i=0;i<36;i++)
	{
	  rand3 = rand()%36;
      temp=chr_set[i];
      chr_set[i]=chr_set[rand3];
      chr_set[rand3]=temp;
	}
	start=time(NULL);
	system("cls");
	draw_check_pattern(6, 6);
	char_display(chr_set);
	gotoxy(1,15);
	printf("%c�� ������ �Է��ϰ� Enter>", chr[rand1]);
    scanf("%d", &number);
	end=time(NULL);
	pst=difftime(end, start);
	gotoxy(1, 17);
	printf("����ð�:%6.2f��, ���ѽð�:%6.2f", pst, time_limit);
	gotoxy(1, 18);
	if (pst<=time_limit)
	{
		if (number==rand2)
			printf("�¾ҽ��ϴ�. ");
		else
			printf("Ʋ�Ƚ��ϴ�. ������ %d���Դϴ�. ", rand2);
	}
	else
		printf("���ѽð� �ʰ��Դϴ�. ������ %d���Դϴ�. ", rand2);
	gotoxy(1, 20);
	printf("����Ͻ÷��� 1, ����� 0�� �Է��ϰ� Enter>");
	scanf("%d", &yes);
	if (!yes)
		exit(1);
}


void display_rule(void)
{
	printf("���� ���ڸ� ã�ƶ�!\n\n");
	printf("�����ǿ� ǥ�õ� ���� b �Ǵ� d��\n");
	printf("������ ������ �����Դϴ�. \n\n");
}

int select_num(void)
{
	int time_limit;
	printf("���̵��� �����ϼ���.\n\n");
	printf("1. �ʱ��ڿ�(���ѽð� 40��)\n");
	printf("2. �߱��ڿ�(���ѽð� 30��)\n");
	printf("3. ����ڿ�(���ѽð� 20��)\n");
    printf("���̵��� �Է��ϰ� Enter>");
	scanf("%d",&time_limit);
	return time_limit;
}

void char_display(char chr_set[])
{
  int i, j, count=0;
  for(i=0;i<6;i++)
	  for(j=0;j<6;j++)
	  {
		  gotoxy(3+4*j, 2+2*i);
		  printf("%c", chr_set[count]);
		  count++;
	  }
}

void draw_check_pattern(int r, int c)
{

	int i, j;
	unsigned char a=0xa6;
	unsigned char b[12]; 
	
	for(i=1;i<12;i++)
		b[i]=0xa0+i;

	printf("%c%c",a, b[3]);
	for(i=0;i<r-1;i++)
		printf("%c%c%c%c", a, b[1], a, b[8]);

	printf("%c%c%c%c", a, b[1], a, b[4]);
	printf("\n");

	for(i=0;i<c-1;i++)
	{
		printf("%c%c", a, b[2]);
		for(j=0;j<r;j++)
			printf("  %c%c",a, b[2]);
		printf("\n");

		printf("%c%c", a, b[7]);
		for(j=0;j<r-1;j++)
			printf("%c%c%c%c", a, b[1], a, b[11]);
		printf("%c%c%c%c",a, b[1],a, b[9]);
		printf("\n");
	}

	printf("%c%c", a, b[2]);
	for(j=0;j<r;j++)
		printf("  %c%c",a, b[2]);
	printf("\n");

	printf("%c%c", a, b[6]);
	for(i=0;i<r-1;i++)
		printf("%c%c%c%c", a, b[1], a, b[10]);
	printf("%c%c%c%c", a, b[1], a, b[5]);
	printf("\n");
}

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}




