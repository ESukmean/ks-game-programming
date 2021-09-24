#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void display_abacus(int m[]);
void gotoxy(int x, int y);
int* div_number(long number, int digit);
int main(void)
{
  long number, sum=0;
  int *mb, digit;
  
	system("cls");
	printf("1부터10까지 합산표시 animation\n");
	
	gotoxy(1, 16);
    for(number=1;number<=10;number++)
	{
		gotoxy(23,3);
		printf("+%2d", number);
		sum+=number;
		digit=(int)log10(sum)+1;
		mb=div_number(sum, digit);
		display_abacus(mb);
		Sleep(1500);
	}
	gotoxy(1,17);
  return 0;
}

int* div_number(long number, int digit)
{
  int *mc=(int*)malloc(digit), i;
  for(i=0;i<=8;i++)
  {
	 mc[i]= (int) (number/pow(10, 8-i));
	 number= number-(long) pow(10, 8-i)*mc[i];
  }
  return mc;
}




void display_abacus(int m[])
{
	int i, j;
	unsigned char a1=0xa6, a2=0xa1;
	gotoxy(3, 4);

	for(i=0;i<=8;i++)
		printf("%2d ", m[i]);
	gotoxy(3, 5);
	for(i=1;i<=15;i++)
		printf("%c%c",a1, 0xa1);
	printf("\n");
	printf("  ");
	for(i=0;i<=8;i++)
		if (m[i]/5)
			printf("%c%c ", a2, 0xdf);
		else
			printf("%c%c ",a1, 0xa2);
	gotoxy(3, 7);
	for(i=0;i<=8;i++)
		if (m[i]<5)
			printf("%c%c ", a2, 0xdf);
		else
			printf("%c%c ",a1, 0xa2);
	for(i=0;i<=8;i++) 
		m[i]%=5;
	gotoxy(3, 8);
	for(i=1;i<=13;i++) 
		printf("%c%c",a1, a2);
	for(i=1;i<=5;i++) 
	{
		gotoxy(3, 8+i);
		for(j=0;j<=8;j++)
		if (m[j]>=i)
			printf("%c%c ", a2, 0xdf);
		else if (m[j]==0) {
			printf("%c%c ", a1, 0xa2);
			m[j]=5;
		}
		else {
			printf("%c%c ", a1, 0xa2);
			m[j]=5;
		}
	}
	printf("\n");
	for(i=1;i<=15;i++)
		printf("%c%c",a1, 0xa1);
	printf("\n");
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
