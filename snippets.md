# ���� ���̴� �ڵ� ������

## GoTo XY �Լ�
```c
#include <conio.h>

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```