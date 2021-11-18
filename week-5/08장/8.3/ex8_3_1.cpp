#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y);

int main(void)
{
	int hour=0, min=0, sec=0, tenms=0;
	char ch;

	gotoxy(1, 3);
	printf("S:Stop/Start");
	gotoxy(1, 4);
	printf("R:Reset");
	gotoxy(1, 5);
	printf("Q:Quit");
	gotoxy(1, 7);
	printf("시 : 분 : 초 : 1/100초");
	do
	{
		gotoxy(1, 8);
		printf("%02d : %02d : %02d : %02d", hour, min, sec, tenms);
		Sleep(10);
		tenms++;
		if(tenms==100)
		{
			sec++;
			tenms=0;
		}
		if(sec==60)
		{
			min++;
			sec=0;
		}
		if(min==60)
		{ 
			hour++;
			min=0;
		}
 
		if(kbhit())
		{
			ch = getch();
			switch(ch)
			{
				case 'S': case 's':
				while(1)
				{
					ch = getch();
					if(ch=='s' || ch=='S') 
						break;
					else if(ch=='r' || ch=='R')
					{
						hour=min=sec=tenms=0;
						break;
					}
				else if(ch=='q' || ch=='Q')
					{
						printf("\n\n");
						return 0;
					}
				} break;
				case 'R': case 'r': 
					hour=min=sec=tenms=0; 
					break;
				case 'Q': case 'q': printf("\n\n"); 
					return 0;
				default : 
					break;
			}
		}
	}while(ch!='q');
	return 0;
}
 

void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
