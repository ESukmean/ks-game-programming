#include <stdio.h>
#include <math.h>

void number_to_hangul(double money);
void comma_display(double money);

int main(void)
{
	double money=12345678912345;
	printf("ÀÔ·ÂµÈ ±Ý¾× = ");
	comma_display(money);
	printf("\n");
	number_to_hangul(money);
	printf("\n");
	return 0;
}

void number_to_hangul(double money)
{
   //[ÇÔ¼ö 11.5.1]ÀÇ Á¤ÀÇºÎºÐ Âü°í
   long num1, num2, temp;
   double m_unit[]={1000000000000, 100000000, 10000, 1};
   double m_unit01[]={1000, 100, 10};
   int i, j;
   char *unit01[]={"ð¼", "åâ", "Ø¿", " êª"};
   char *unit02[]={"ô¶", "ÛÝ", "ä¨"};
   char *unit03[]={"  ", "ìé", "ì£", "ß²", "ÞÌ", "çé", 
                        "ë»", "öÒ", "ø¢", "Îú"};
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
	length=(long) (log10(money)/log10(10)+1);   //[¿¹Á¦ 2.2.11] ½ÊÁø¼öÀÇ ÀÚ¸®¼ö °è»ê 

	for(i=length;i>=1;i--)                      //5.4.2Àý ±Ý¾×¿¡ ´ëÇÑ ÄÞ¸¶Ç¥½Ã
	{
		number=  (long) (money/ pow(10, i-1));
		printf("%ld", (long) number);
		if ((i-1)%3==0 && (i-1)>0)
			printf(",");
		money=money - number*pow(10,i-1);
	}
}

