#include <stdio.h>
#include <string.h>


int digits[10][20] = {
	{1, 1, 1, 1,
	 1, 0, 0, 1,
	 1, 0, 0, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1},
	{0, 0, 1, 0,
	 0, 0, 1, 0,
	 0, 0, 1, 0,
	 0, 0, 1, 0,
	 0, 0, 1, 0},
	{1, 1, 1, 1,
	 0, 0, 0, 1,
	 1, 1, 1, 1,
	 1, 0, 0, 0,
	 1, 1, 1, 1},
	{1, 1, 1, 1,
	 0, 0, 0, 1,
	 1, 1, 1, 1,
	 0, 0, 0, 1,
	 1, 1, 1, 1},
	{1, 0, 0, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1,
	 0, 0, 0, 1,
	 0, 0, 0, 1},
	{1, 1, 1, 1,
	 1, 0, 0, 0,
	 1, 1, 1, 1,
	 0, 0, 0, 1,
	 1, 1, 1, 1},
	{1, 0, 0, 0,
	 1, 0, 0, 0,
	 1, 1, 1, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1},
	{1, 1, 1, 1,
	 0, 0, 0, 1,
	 0, 0, 0, 1,
	 0, 0, 0, 1,
	 0, 0, 0, 1},
	{1, 1, 1, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1},
	{1, 1, 1, 1,
	 1, 0, 0, 1,
	 1, 1, 1, 1,
	 0, 0, 0, 1,
	 0, 0, 0, 1},
};
char print_map[2][4] = { " ", "бс" };

int main() {
	char input_f[41];
	scanf("%40s", &input_f);

	int len = strlen(input_f);

	for (int line = 0; line < 5; line++) {
		for (int pos = 0; pos < len; pos++) {
			printf("%s", print_map[digits[input_f[pos] - '0'][line * 4 + 0]]);
			printf("%s", print_map[digits[input_f[pos] - '0'][line * 4 + 1]]);
			printf("%s", print_map[digits[input_f[pos] - '0'][line * 4 + 2]]);
			printf("%s", print_map[digits[input_f[pos] - '0'][line * 4 + 3]]);
			printf(" ");
		}
		printf("\n");
	}
}