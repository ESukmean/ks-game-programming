#include <stdio.h>
int main(void)
{
   unsigned long money, num;
   unsigned long m_unit[]={100000000,
                                10000, 1};
   int i;
   char *unit01[]={"억", "만", "원"};	
   printf("금액을 입력하고 Enter>");
   scanf("%ld", &money);
   printf("\n화폐단위\n");
   for(i=0; i<3; i++)
   {
 	num=money/m_unit[i];
	if(!num)
		continue;
	printf("%ld%s ", num, unit01[i]);
	money=money-num*m_unit[i];
   }
   printf("\n");
   return 0;
}
