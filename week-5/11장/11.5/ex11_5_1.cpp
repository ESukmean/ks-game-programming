#include <stdio.h>
#include <math.h>

void number_to_hangul(double money);
void comma_display(double money);

int main(void)
{
	double money=12345678912345;
	printf("입력된 금액 = ");
	comma_display(money);
	printf("\n");
	number_to_hangul(money);
	printf("\n");
	return 0;
}

void number_to_hangul(double money)
{
   //[함수 11.5.1]의 정의부분 참고
   long num1, num2, temp;
   double m_unit[]={1000000000000, 100000000, 10000, 1};
   double m_unit01[]={1000, 100, 10};
   int i, j;
   char *unit01[]={"조", "억", "만", "원"};
   char *unit02[]={"천", "백", "십"};
   char *unit03[]={"  ", "일", "이", "삼", "사", "오", 
                        "육", "칠", "팔", "구"};
   for(i=0; i<4; i++)
   {
      num1=(long) (money/m_unit[i]);
      if(!num1)
          continue;
      temp=num1;
      for(j=0;j<3;j++)
      {
			num2=(long) (num1/m_unit01[j]);
			if (!num2)
				continue;
			printf("%s%s", unit03[num2], unit02[j]);
			num1=num1-(long)(num2*m_unit01[j]);
      }
      printf("%s%s ", unit03[num1], unit01[i]);
      money=money-temp*m_unit[i];

   }
}


void comma_display(double money)
{
	double number; 
	long length, i;
	length=(long) (log10(money)/log10(10)+1);   //[예제 2.2.11] 십진수의 자리수 계산 

	for(i=length;i>=1;i--)                      //5.4.2절 금액에 대한 콤마표시
	{
		number=  (long) (money/ pow(10, i-1));
		printf("%ld", (long) number);
		if ((i-1)%3==0 && (i-1)>0)
			printf(",");
		money=money - number*pow(10,i-1);
	}
}

