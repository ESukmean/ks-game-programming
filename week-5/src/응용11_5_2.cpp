#include <stdio.h>
int main(void)
{
   unsigned long money, num1, num2, temp;
   unsigned long m_unit[]={100000000,
                                   10000, 1};
   unsigned long m_unit01[]={1000, 100,
                                   10};
   int i, j;
   char *unit01[]={"억", "만", "원"};
   char *unit02[]={"천", "백", "십"};
   printf("금액을 입력하고 Enter>");
   scanf("%ld", &money);
   printf("\n화폐단위\n");
   for(i=0; i<3; i++)
   {
      num1=money/m_unit[i];
      if(!num1)
	  continue;
      temp=num1;
      for(j=0;j<3;j++)
      {
         num2=num1/m_unit01[j];
         if (!num2)
            continue;
         printf("%ld%s", num2, unit02[j]);
	 num1=num1-num2*m_unit01[j];
      }
      printf("%ld%s ", num1, unit01[i]);
      money=money-temp*m_unit[i];
   }
   printf("\n");
   return 0;
}
