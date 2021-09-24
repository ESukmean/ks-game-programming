#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void move_shape(int m[][3], int landing);
void print_shape(int m[][3]);		
void landing_location(int landing);
void gotoxy(int x, int y);
void intro_game(int m[][3]);
void game_control(int m[][3]);


int x=35, y=1;
int inx=0, iny=0;

int main(void)
{
	int shape1[3][3]={0,1,0,
		              1,1,1,
					  1,0,1};

	intro_game(shape1);
	game_control(shape1);
	return 0;
}


void game_control(int m[][3])
{
	char key=0;
	int landing;
	x=35;
	y=1;
	srand(time(NULL));
	landing=rand()%70+1;
	do
	{
		while(!kbhit())
		{
			system("cls");
			move_shape(m, landing);
		}
		if (y>22)
			break;
		key=getch();
		switch(key)
		{
			/*
			case 72 : 
				inx=0;
				iny=-1;
				move_shape(shape1, shape2, landing);		
				break;
			*/
			case 75 : 
				inx=-1;
				iny=0;
				move_shape(m, landing);		
				break;
			case 77 : 
				inx=1;
				iny=0;
				move_shape(m, landing);		
				break;
			case 80 : 
				inx=0;
				iny=1;
				move_shape(m, landing);		
				break;
			default :
				break;
		}
	}while(y<22);
	if (x==landing)
		printf("��������!\n");
	else
		printf("��������!");
	getch();
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void intro_game(int m[][3])
{
	printf("���ּ� ����\n\n");
	printf("���ּ��� �ش� ��ġ��\n");
	printf("������Ű�� �����Դϴ�. \n\n");
	printf("���ּ��� ȭ�� ���� ��ġ�ϴµ�\n");
	printf("ȭ��ǥŰ�� �̿��Ͽ� ���������� \n");
	printf("��Ȯ�� �������Ѿ� �մϴ�.\n\n");
	printf("���ּ� ���        ������ġ\n");
	x=1;
	y=11;
	print_shape(m);	
	gotoxy(20, 11);
	printf("����");
	gotoxy(1, 15);
    printf("�ƹ�Ű�� ������ �����մϴ�.\n");
	getch();
}


void landing_location(int landing)
{
	int i;
	gotoxy(landing, 23);
	for(i=0;i<3;i++)
		printf("��");
}



void move_shape(int m[][3], int landing)		
{
	do
	{
		system("cls");
		print_shape(m);
		x=x+inx;
		y=y+iny;
		if (y<1)
			y=1;
		if (x>75)
			x=75;
		else if (x<1)
			x=1;
		Sleep(100);
		if (y>21)
			return;
		landing_location(landing);
	}while(!kbhit());
}


void print_shape(int m[][3])		
{
	int i, j;
	for(i=0;i<3;i++)
	{
		gotoxy(x,y+i);
		for(j=0;j<3;j++)
			if (m[i][j]==1)
				printf("��");
			else
				printf("  ");
		printf("\n");
	}
}

