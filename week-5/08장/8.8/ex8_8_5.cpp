#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void heap_sort(int* , int);
void heap(int* ,int, int);

int main(void)
{
	int num[45], sel[6];
	int times, range, index, move;
        srand(time(NULL));
	printf("로또 당첨 번호 \n\n");
	printf("아무키나 누르면 시작합니다.\n");
	getch();


	for(index=0;index<=44;index++)
	num[index]=index+1;

	for(times=0;times<=5;times++)
	{
		range=45-times;
		index=rand()%range;
		sel[times]=num[index];

		if(index==44-times)
			  continue;
			else
		  {
			  for(move=index;move<=44-times;move++)
						num[move]=num[move+1];
			}
	}

// print result

	for(index=0;index<=5;index++)
		printf("\n%d번째 당첨번호 : %2d ",index+1, sel[index]);
	heap_sort(sel, 5);
	printf("\n\n[당첨 번호 정렬]\n");
	for(index=0;index<=5;index++)
		printf("%d ",sel[index]);
	printf("\n");
	return 0;
}

//heap sort program
void heap_sort(int *b, int n)
{
	int k, t;
	for (k = n / 2; k >= 0; k--)
	heap(b, n, k);
	while (n > 0)
		{
			t = b[0];
			b[0] = b[n];
			b[n] = t;
			heap(b, --n, 0);
		}
}

void heap(int *b, int n, int k)
{
	int j, v;
	v = b[k];
	while (k <= n / 2)
		{
			j = k+k;
			if (j < n && b[j] < b[j+1])
				j++;
			if (v >= b[j])
				break;
			b[k] = b[j];
			k = j;
		}
 b[k] = v;
}

