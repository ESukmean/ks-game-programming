//동요 노래방
// 곡목 2개 : 곰 세마리, 사과같은 내얼굴
// 곰세마리의 가사는 s1_lyrics.txt에, 악보는 s1_music.txt에 저장되어 있음 
// 사과같은 내열굴의 가사는 s2_lyrics.txt에, 악보는 s2_music.txt에 저장되어 있음  

// 악보에는 계명과 음의 길이가 저장되어 있음 
// 계명은 숫자로 입력되어 있음. 예로 1은 도, 3은 미  
// 음의 길이 8분음표의 길이는 250, 4분음표의 길이는 500, 2분음표의 길이는 1000

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void display_piano_keyboard(void);
void touch_keyboard(int code);

void sing_a_song(char title[], char lyrics[], char music[]); //노래와 가사 선택

int menu_display(void);
void play_piano(void);           //메모리(배열)에 저장된 내용을 재생 
void load_music(char music[]);   //파일에 저장된 주파수와 음의 지연시간을 불러옴(악보)
void load_lyrics(char lyrics[]);  //파일에 저장된 가사 불러옴(가사)

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
			case 1 : sing_a_song("곰 세마리", "s1_lyrics.txt", "s1_music.txt");
				break;
			case 2 : sing_a_song("사과같은 내얼굴", "s2_lyrics.txt", "s2_music.txt");
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
 printf("동요 노래방\n\n");
 printf("1. 곰 세마리\n");
 printf("2. 사과같은 내얼굴\n");
 printf("0. 프로그램 종료\n\n");
 printf("곡목번호 선택>");
 select=getch();
 return select-'0';
}

void sing_a_song(char title[], char lyrics[], char music[])
{
	system("cls");
	gotoxy(1, 1);
	printf("동요 제목 : %s", title);

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
 printf("아무키를 누르면 main으로 돌아갑니다....");
 getch();
}

void press_start(void)
{
 gotoxy(1,20);
 printf("아무키를 누르면 시작합니다....");
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
		printf("저장된 음악이 없습니다.\n");
	presskey();
}


void display_piano_keyboard(void)
{
	unsigned char start=0xb1;
	unsigned char loc=0xa3, i;
	char code[8][4]={"도", "레", "미", "파", "솔", "라", "시", "도"};
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

//파일에 저장된 주파수와 음의 지연시간을 불러옴(악보)
void load_music(char music[])  
{
	FILE *fp;
	int count=0;
	fp=fopen(music, "r");
	if (fp==NULL)
	{
		printf("파일처리 오류발생. 프로그램 종료\n");
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

//파일에 저장된 가사를 불러옴(가사)
void load_lyrics(char lyrics[])  
{
	char chr[61];
	FILE *fp;

	fp=fopen(lyrics, "r");
	if (fp==NULL)
	{
		printf("파일처리 오류발생. 프로그램 종료\n");
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

