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
			c[i * 13 + j].number = j;
		}
	}
}
void print_card(struct card c)
{
	char cardno = '0' + c.number;
	switch (c.number)
	{
	case 0:
		cardno = 'A';
		break;
	case 10:
		cardno = 'J';
		break;
	case 11:
		cardno = 'Q';
		break;
	case 12:
		cardno = 'K';
		break;
	default:
		break;
	}

	printf("%s	%c\n", c.shape, cardno);
}
void shuffle_card(struct card *c) {
	srand(time(NULL));

	for(int i = 0; i < 53; i++) {
		int rnd = rand() % 53;
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

	shuffle_card(cardlist);
	// for(int i=0; i < 53; i++) {
	// 	print_card(cardlist[i]);
	// 	printf("\n");
	// }

	for (int i = 0; i < 5; i++)
	{
		print_card(cardlist[i]);
	}
}