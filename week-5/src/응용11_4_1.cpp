#include <stdio.h>
char *ms_char[10]={"센티미터", "미터", "킬로미터", "인치", "피트"
		 ,"야드", "마일", "자(척)", "간", "리"};
void print_distance_unit(void);
void measure_calculate(int basic, int transe, double measure);

int main(void)
{
  double measure;
  int basic, transe;

  printf("길이에 대한 도량형 환산 프로그램\n\n");
  print_distance_unit();
  printf("\n\n기본단위와 변환단위\n입력 후 Enter(예:1 5)>");
  scanf("%d %d",&basic,&transe);

  printf("값을 입력하고 Enter>");
  scanf("%lf", &measure);
  printf("\n");
  measure_calculate(basic, transe, measure);
  return 0;
}

void print_distance_unit(void)
{
	int i;
	for(i=0;i<=9;i++)
	{
		printf("%d:%-8s  ", i, ms_char[i]);
		if (i%3==2)
			printf("\n");
	}
}

void measure_calculate(int basic, int transe, double measure)
{
  //[함수 11.4.1]의 정의 부분 참고
  double msre[10], unit, result;

  msre[0]=392772;		//centimeter
  msre[1]=msre[0]/100.;	//meter
  msre[2]=msre[1]/1000.;	//kilometer
  msre[3]=msre[0]/2.54;	//inch
  msre[4]=msre[3]/12.;	//feet
  msre[5]=msre[4]/3.;	//yard 
  msre[6]=msre[5]/1760.;	//mile
  msre[7]=12960.;      	//자
  msre[8]=msre[7]/6.;   	//간
  msre[9]=msre[8]/(6.*36); //리

  unit=msre[basic];
  result=measure*(msre[transe]/unit);
  printf("%.2f %8s는 ", measure, ms_char[basic]);
  printf("%15.5f %8s\n", result, ms_char[transe]);
}
