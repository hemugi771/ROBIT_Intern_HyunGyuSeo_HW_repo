#include <stdio.h>

int main(void)
{
	float a, b, max, min, sum;
	printf(" 1 번째 실수를 입력하시오. ");
	scanf_s("%f", &a);
	sum = a;
	max = a;
	min = a;
	for (int i = 2; i < 6; i++)
	{
		printf("%d번째 실수를 입력하시오. ", i);
		scanf_s("%f", &b);
		max = (max > b) ? max : b;
		min = (min > b) ? b : min;
		sum += b;
	}
	printf("평균은 %f입니다.\n최댓값은 %f입니다.\n최솟값은 %f입니다.", sum / 5, max, min);
}