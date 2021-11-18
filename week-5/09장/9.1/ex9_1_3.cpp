//���� �뷡��
// ��� 2�� : �� ������, ������� ����
// ���������� ����� s1_lyrics.txt��, �Ǻ��� s1_music.txt�� ����Ǿ� ���� 
// ������� �������� ����� s2_lyrics.txt��, �Ǻ��� s2_music.txt�� ����Ǿ� ����  

// �Ǻ����� ���� ���� ���̰� ����Ǿ� ���� 
// ����� ���ڷ� �ԷµǾ� ����. ���� 1�� ��, 3�� ��  
// ���� ���� 8����ǥ�� ���̴� 250, 4����ǥ�� ���̴� 500, 2����ǥ�� ���̴� 1000

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void display_piano_keyboard(void);
void touch_keyboard(int code);

void sing_a_song(char title[], char lyrics[], char music[]); //�뷡�� ���� ����

int menu_display(void);
void play_piano(void);           //�޸�(�迭)�� ����� ������ ��� 
void load_music(char music[]);   //���Ͽ� ����� ���ļ��� ���� �����ð��� �ҷ���(�Ǻ�)
void load_lyrics(char lyrics[]);  //���Ͽ� ����� ���� �ҷ���(����)

void draw_check02(int c, int r);
void gotoxy(int x, int y);
void presskey(void);
void press_start(void);

char touch[100];
unsigned long time_check[100];
char rec_check=0;



int main(void)
{
	int c;
	while(c=menu_display())
	{
		switch(c)
		{
			case 1 : sing_a_song("�� ������", "s1_lyrics.txt", "s1_music.txt");
				break;
			case 2 : sing_a_song("������� ����", "s2_lyrics.txt", "s2_music.txt");
				break;
			default : break;
	}
 }
 return 0;
}

int menu_display(void)
{
 char select;
 system("cls");
 printf("���� �뷡��\n\n");
 printf("1. �� ������\n");
 printf("2. ������� ����\n");
 printf("0. ���α׷� ����\n\n");
 printf("����ȣ ����>");
 select=getch();
 return select-'0';
}

void sing_a_song(char title[], char lyrics[], char music[])
{
	system("cls");
	gotoxy(1, 1);
	printf("���� ���� : %s", title);

	gotoxy(1, 3);
	draw_check02(8, 2);
	display_piano_keyboard();

	load_lyrics(lyrics);
	load_music(music);
	press_start();
	play_piano();
}


void presskey(void)
{
 gotoxy(1,20);
 printf("�ƹ�Ű�� ������ main���� ���ư��ϴ�....");
 getch();
}

void press_start(void)
{
 gotoxy(1,20);
 printf("�ƹ�Ű�� ������ �����մϴ�....");
 getch();
}


void play_piano(void)
{
	int freq[]={523,587,659,698,784,880,988,1046};
	int code, count=0;
	gotoxy(1, 3);
	if (rec_check)
	{
		do
		{
			code=touch[count];
			if (1<=code && code<=8)
			{
				touch_keyboard(code-1);
				Beep(freq[code-1], time_check[count]);
			}
			count++;
			display_piano_keyboard();
		}while(code!=27);
	}
	else
		printf("����� ������ �����ϴ�.\n");
	presskey();
}


void display_piano_keyboard(void)
{
	unsigned char start=0xb1;
	unsigned char loc=0xa3, i;
	char code[8][4]={"��", "��", "��", "��", "��", "��", "��", "��"};
	for(i=0;i<8;i++)
	{
		gotoxy(3+i*4,4);
		printf("%c%c", loc, start+i);
	}

	for(i=0;i<8;i++)
	{
		gotoxy(3+i*4,6);
		printf("%s", code[i]);
	}

}




void touch_keyboard(int code)
{
		gotoxy(3+code*4,6);
		printf("%c%c", 0xa1, 0xe3);
}

//���Ͽ� ����� ���ļ��� ���� �����ð��� �ҷ���(�Ǻ�)
void load_music(char music[])  
{
	FILE *fp;
	int count=0;
	fp=fopen(music, "r");
	if (fp==NULL)
	{
		printf("����ó�� �����߻�. ���α׷� ����\n");
		exit(1);
	}
	while(!feof(fp))
	{
		fscanf(fp, "%d %ld\n", &touch[count], &time_check[count]);
		count++;
	}
	touch[count]=27;
	fclose(fp);
	rec_check=1;
}

//���Ͽ� ����� ���縦 �ҷ���(����)
void load_lyrics(char lyrics[])  
{
	char chr[61];
	FILE *fp;

	fp=fopen(lyrics, "r");
	if (fp==NULL)
	{
		printf("����ó�� �����߻�. ���α׷� ����\n");
		exit(1);
	}
	gotoxy(1, 9);
	while(!feof(fp))
	{
		fgets(chr, 60, fp);
		printf("%s\n", chr);
	}
	fclose(fp);
}





void draw_check02(int c, int r)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++)
	b[i]=0xa0+i;
    printf("%c%c",a, b[3]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[8]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for(i=0;i<r-1;i++)
    {
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++)
	{
		printf("  ");
		printf("%c%c",a, b[2]);
	}
	printf("\n");
	printf("%c%c", a, b[7]);
	for(j=0;j<c-1;j++)
	{
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[11]);
	}
	printf("%c%c",a, b[1]);
	printf("%c%c",a, b[9]);
	printf("\n");
    }
    printf("%c%c", a, b[2]);
    for(j=0;j<c;j++)
    {
	printf("  ");
	printf("%c%c",a, b[2]);
    }
    printf("\n");
    printf("%c%c", a, b[6]);
    for(i=0;i<c-1;i++)
    {
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[10]);
    }
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

