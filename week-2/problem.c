#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct card
{
	char shape[3];
	char number;
};

void init_card(struct card *c)
{
	const char shape[4][3] = {"¢¼", "¡ß", "¢¾", "¢À"};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			memcpy(&(c[i * 13 + j].shape), &(shape[i]), 3);
			c[i * 13 + j].number = j + 1;
		}
	}
}
void print_card(struct card c)
{
	char cardno[3] = {'0' + c.number, 0, 0};

	switch (c.number)
	{
	case 1:
		cardno[0] = 'A';
		break;
	case 10:
		cardno[0] = '1';
		cardno[1] = '0';
		break;
	case 11:
		cardno[0] = 'J';
		break;
	case 12:
		cardno[0] = 'Q';
		break;
	case 13:
		cardno[0] = 'K';
		break;
	default:
		break;
	}

	printf("%s	%s\n", c.shape, cardno);
}
void shuffle_card(struct card *c) {
	srand(time(NULL));

	for(int i = 0; i < 52; i++) {
		int rnd = rand() % 52;
		// printf("rnd %d\n", rnd);

		struct card tmp = c[i];
		c[i] = c[rnd];
		c[rnd] = tmp;
	}
}
int main()
{
	struct card cardlist[52];
	init_card(cardlist);
	// for(int i=0; i < 52; i++) {
	// 	print_card(cardlist[i]);
	// }

	shuffle_card(cardlist);
	printf("\n");

	for (int i = 0; i < 5; i++)
	{
		print_card(cardlist[i]);
	}
}