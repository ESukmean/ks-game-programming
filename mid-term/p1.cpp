#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

const int hakbun = 2017648070;
const char* name = "�̼���";
const char* hakbun_str = "2017648070";

void menu();
void print(int type);
void clear();
void warning(char* str);


int main() {
	menu();	
	int in_menu = 1;

	int chr = getch();
	while(chr != '0') {
		if (in_menu == 0) { clear(); menu(); in_menu = 1; chr = getch(); continue; }

		int type = (chr - '0');
		if (type > 0 && type < 4) {
			clear();
			print(type);
			in_menu = 0;
		} else if (type == 0) {
			break;
		} 
		else {
			warning("�߸��� Ű�� ���Ƚ��ϴ�.");
		}

		chr = getch();
	}

	return 0;
}

void clear() {
	system("cls");
}
void menu() {

	printf(" ---------------- �й� �̸� ��� ���α׷� ----------- \n");
	printf(" ---------------- -------- �޴� -------- ----------- \n");

	printf("\n\n");
	printf("1. �й� ���\n");
	printf("2. �̸� ���\n");
	printf("3. �й��� �̸� ���\n");
	printf("0. ���α׷� ����\n");
}
void print(int type) {
	int row = 70 % 15;
	int col = 80 % 40;

	for (int i = 0; i < row; i++) {
		printf("\n");
	}
	for (int i = 0; i < col; i++) {
		printf(" ");
	}

	gotoxy(row, col); // �� �ȵǴ°� ���Ƽ�.. ����÷�
	
	if (type == 1 || type == 3) {
		printf("%d ", hakbun);
	}
	if (type == 2 || type == 3) {
		printf("%s", name);
	}
}
void warning(char* str) {
	gotoxy(3, 10);
	printf("%s", str);
}