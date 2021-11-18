#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void) {
	gotoxy(10, 20);
	system("cls");

	int chr = getch(); // 0 또는 224 받음.
	if (chr == 0 || chr == 224) {
		chr = getch(); // 확장키
	} else {
		// ascii
	}

	printf("%c%c", 0xa6, 0xa3);
	printf("%c%c", 0xa6, 0xa4);
	printf("%c%c", 0xa6, 0xa5);
	printf("%c%c", 0xa6, 0xa6);

	srand(time(NULL)); 


	Beep(121, 2000);
	return 0;
}