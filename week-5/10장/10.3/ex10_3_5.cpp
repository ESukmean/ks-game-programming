#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void moving_character_signboard(char file_name1[], char file_name2[], int line_length);
void gotoxy(int x, int y);
void draw_rectangle(int c, int r);

int main(void)
{
	char file_name1[20]="pizza.txt";
	char file_name2[20]="stock.txt";
	int line_length=20;

	printf("움직이는 글자 광고판\n\n");
	moving_character_signboard(file_name1, file_name2, line_length);
	return 0;
}

void moving_character_signboard(char file_name1[], char file_name2[], int line_length)
{
    //[함수 10.3.1]의 정의 부분 참고
	char *ptr1, *ptr1, chr1[121], chr2[121];
	int i, j, length, count=0, countx;
	FILE *fp1, *fp2;
	ptr1=(char *)malloc(line_length);
	ptr2=(char *)malloc(line_length);
	gotoxy(1, 9);
	draw_rectangle(line_length/2, 1);
	fp1=fopen(file_name1, "r");
	fp2=fopen(file_name1, "r");
	if ((fp1==NULL) || (fp2==NULL))
	{
		printf("file open error!");
		exit(1);
	}
	while(!feof(fp1))
	{
		//부분 1의 처리
		fgets(chr1, 120, fp1);
		fgets(chr2, 120, fp2);

		length1=strlen(chr1);
		ptr1[line_length]='\0';
		for(j=0;j<line_length;j++)          
		{
			count=0;
			for(i=0;i<line_length-j-1;i++)
				ptr[i]=' ';
			for(i=line_length-j-1;i<line_length;i++)
			{
				ptr1[i]=chr1[count];
				count++;
			}
			gotoxy(3, 10);
			Sleep(200);
			printf("%s", ptr1);
		}
		//부분 2의 처리 
		count=1;
		for(j=line_length-2;j<length;j++)  
		{
			countx=0;		
			for(i=count;i<count+line_length;i++)
			{
				ptr[countx]=chr[i];
				countx++;
			}
			count++;
			if ((length-line_length)<=count)
				break;
			gotoxy(3, 10);
			Sleep(200);
			printf("%s", ptr);
		}
		//부분 3의 처리
		for(j=0;j<line_length;j++)		
		{
			for(i=0;i<line_length-j-1;i++)
				ptr[i]=ptr[i+1];
			for(i=line_length-j-1;i<line_length;i++)
				ptr[i]=' ';
			gotoxy(3, 10);
			Sleep(200);
			printf("%s", ptr);
		}
	}
	gotoxy(1, 12);
	fclose(fp);
}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void draw_rectangle(int c, int r)
{
    //[함수 3.5.2]의 정의부분 참고
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
   	b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<c;i++)
  	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r;i++)
    {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
		printf("  ");
	printf("%c%c",a, b[2]);
	printf("\n");
    }
    printf("%c%c", a, b[6]);
    for(i=0;i<c;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}
