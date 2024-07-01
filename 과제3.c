#include <stdio.h>

int main(void)
{
	int year, a = 0;
	printf("년도를 입력하세요 : ");
	scanf_s("%d", &year);
	if (year % 4 == 0) {//4의 배수이면
		a = 1;//윤년
		if (year % 100 == 0) {//4의 배수이면서 100의 배수이면
			a = 0;//윤년 아님
			if (year % 400 == 0)//4의 배수이면서 100의 배수이면서 400의 배수이면
			{
				a = 1;//윤년
			}
		}
	}
	if (a == 0) {
		printf("윤년 아님");
	}
	else{
		printf("윤년");
	}
}