#include <stdio.h>
#include <conio.h>
#include <windows.h>

int menu_display(void);		  //주메뉴 표시;
int sub_menu_display01(void); //서브메뉴1 표시
int sub_menu_display02(void); //서브메뉴2 표시
void sub_main01(void);        //서브메뉴 1 제어
void sub_main02(void);        //서브메뉴 2 제어
void press_any_key(void);     //아무키나 누르면 이전 메뉴로 

void display_recipe(void);    //레시피 출력
void volume_calculation(void);//부피환산
void weight_calculation(void);//무게환산
void print_unit(char *ms_char[], int n);
void volume_calculate(int basic, int transe, double measure, char *ms_char[]);
void weight_calculate(int basic, int transe, double measure, char *ms_char[]);

int main(void)
{
	int c;
	while((c=menu_display())!=3)
	{
		switch(c)
		{
			case 1 : sub_main01();
				break;
			case 2 : sub_main02();
				break;
			default : break;
		}
	}
	printf("\n");
	return 0;
}
int menu_display(void)
{
    int select;
    system("cls");
    printf("디지털 레시피\n\n");
    printf("1. 레시피 \n");
    printf("2. 단위환산 \n");
    printf("3. 프로그램 종료\n\n");
    printf("메뉴번호 입력>");
    select=getch()-48;
    return select;
}

void sub_main01(void)
{
    int c;
    while((c=sub_menu_display01())!=2)
    {
      switch(c)
      {
           case 1 : display_recipe();
  	 	     break;
           default : break;
     }
   }
}

int sub_menu_display01(void)
{
    int select;
    system("cls");
    printf("레시피\n\n");
    printf("1. 카르보나나라\n");
    printf("2. 메인 메뉴로 이동\n\n");
    printf("메뉴번호 입력>");
    select=getch()-48;
    return select;
}
void sub_main02(void)
{
    int c;
    while((c=sub_menu_display02())!= 3)
    {
      switch(c)
      {
           case 1 : volume_calculation();
  	 	     break;
           case 2 : weight_calculation();
  		     break;
           default : break;
     }
   }
}

int sub_menu_display02(void)
{
        int select;
        system("cls");
        printf("단위환산\n\n");
        printf("1. 부피(volume) 환산 \n");
        printf("2. 무게(weight) 환산 \n");
        printf("3. 메인 메뉴로 이동\n\n");
        printf("메뉴번호 입력>");
        select=getch()-48;
        return select;
}

void press_any_key(void)
{
       printf("\n\n");
       printf("아무키나 누르면 이전 메뉴로...");
       getch();
}
void display_recipe(void)
{
  //[함수 9.2.6]의 정의 부분 참고
	FILE *fp1;
	char chr1[82];
	char *file1="carbonara.txt";
	fp1=fopen(file1, "r");
	system("cls");
	while(!feof(fp1))
	{
		fgets(chr1, 80, fp1);
		if (chr1[0]==10)
		{
			printf("\n다음단계로 이동하려면 아무키나 누르시오.");
			getch();
			system("cls");
		}
		else
			printf("%s", chr1);
	}
	printf("\n레시피 끝.\n");
	press_any_key();
	fclose(fp1);
}

void volume_calculation(void)
{
  //[함수 9.2.1]의 정의 부분 참고
  char *ms_char[6]={"밀리리터", "teaspoon", "tablespoon", 
                     "cup", "리터", "갤런"};
  double measure;
  int basic, transe;
  system("cls");	
  printf("부피에 대한 도량형 환산 프로그램\n\n");
  print_unit(ms_char, 6);
  printf("\n\n기본단위와 변환단위\n입력 후 Enter(예:1 5)>");
  scanf("%d %d",&basic,&transe);
  printf("값을 입력하고 Enter>");
  scanf("%lf", &measure);
  printf("\n");
  volume_calculate(basic, transe, measure, ms_char);
  press_any_key();
}

void weight_calculation(void)
{
  //[함수 9.2.2]의 정의 부분 참고
  char *ms_char[4]={"그램", "온즈", "파운드", "킬로그램"};
  double measure;
  int basic, transe;
  system("cls");	
  printf("무게에 대한 도량형 환산 프로그램\n\n");
  print_unit(ms_char, 4);
  printf("\n\n기본단위와 변환단위\n입력 후 Enter(예:1 5)>");
  scanf("%d %d",&basic,&transe);

  printf("값을 입력하고 Enter>");
  scanf("%lf", &measure);
  printf("\n");
  weight_calculate(basic, transe, measure, ms_char);
  press_any_key();

}

void print_unit(char *ms_char[], int n)
{
 	 //[함수 9.2.5]의 정의 부분 참고
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d:%-9s  ", i, ms_char[i]);
		if (i%3==2)
			printf("\n");
	}
}

void volume_calculate(int basic, int transe, double measure, char *ms_char[])
{
  //[함수 9.2.3]의 정의 부분 참고
  double msre[10], unit, result;
  msre[0]=3758.279;
  msre[1]=msre[0]/5.;
  msre[2]=msre[1]/3.;
  msre[3]=msre[2]/16.667;
  msre[4]=msre[3]/4.;
  msre[5]=msre[4]/3.758;
  unit=msre[basic];
  result=measure*(msre[transe]/unit);
  printf("%.3f %-10s : ", measure, ms_char[basic]);
  printf("%.3f %-10s", result, ms_char[transe]);
}
void weight_calculate(int basic, int transe, double measure, char *ms_char[])
{
  //[함수 9.2.4]의 정의 부분 참고
  double msre[4], unit, result;
  msre[0]=1000;
  msre[1]=msre[0]/28.3459;
  msre[2]=msre[1]/16.;
  msre[3]=msre[2]/2.205;
  unit=msre[basic];
  result=measure*(msre[transe]/unit);
  printf("%.2f %-8s:", measure, ms_char[basic]);
  printf("%.5f %-8s", result, ms_char[transe]);
}
