#include <stdio.h>

int main() {
	char string[20];
	char c;	
	printf("문자열 입력: ");
	scanf("%s", string);
	printf("문자 입력: ");
	if ((c = getchar()) == '\n') {
		// 파일을 stdin으로 feeding 할 수도 있고.. 하니까 \n이 들어왔을때만 새로 한글자 더 입력받도록 함
		scanf("%c", &c);	
	}
	
	
	printf("%s\n", string);
	printf("!!%c!!\n", c);
	
	return 0;	
}