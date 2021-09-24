#include <stdio.h>
#include <time.h>
#include <windows.h>

void seat_arrangement(int row, int column, int students, int obstacle[][7]);
void shuffle_number(int sit_number[], int total);
void draw_check02(int column, int row);
void gotoxy(int x, int y);

int main(void)
{
	int row=7, column=7, students=40;  //�� 7, �� 7, �л��� 40��
	int obstacle[7][7]={0};   //��ֹ��� ��ġ ����

	printf("��ֹ��� �ִ� �ڸ���ġ ���α׷�\n\n");
	printf("�� 4���� ��ֹ��� �ֽ��ϴ�. \n");

	//��ֹ��� ��ġ(��,��) �Է�, ��ֹ� �� 4�� 
	obstacle[3][3]=1;
	obstacle[3][4]=1;
	obstacle[4][3]=1;
	obstacle[4][4]=1;

	seat_arrangement(row, column, students, obstacle);
	printf("\n\n\n");
	return 0;
}
void seat_arrangement(int row, int column, int students, int obstacle[][7])
{
  //[�Լ� 10.4.2]�� ���� �κ� ����
	int sit_number[100]={0};
	int total, i, j, count=0;
	total=students;
	for(i=0;i<total;i++)
		sit_number[i]=i+1;
	shuffle_number(sit_number, total);
	gotoxy(1, 7);
	draw_check02(column, row);
	for(i=1;i<=row;i++)
	{
		for(j=1;j<=column;j++)
		{
			gotoxy(j*4-1,6+i*2);
			if ((count<students) && (obstacle[i][j]!=1))
			{
				printf("%2d",sit_number[count]);
				count++;
			}
			else if ((obstacle[i][j]==1) && (count<students)) 
			{
				printf("��");
			}
		}
	}
}
void shuffle_number(int sit_number[], int total)
{
  //[�Լ� 10.4.1]�� ���� �κ� ����
	int i, rnd, temp;
	srand(time(NULL));
	for(i=0;i<total;i++)
	{
		rnd=rand()%total;
		temp=sit_number[rnd];
		sit_number[rnd]=sit_number[i];
		sit_number[i]=temp;
	}
}
void draw_check02(int c, int r)
{
  //[�Լ� 3.5.4]�� ���� �κ� ����
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
