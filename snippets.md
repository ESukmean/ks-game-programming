# 자주 쓰이는 코드 스니핏

## GoTo XY 함수
```c
#include <conio.h>

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```