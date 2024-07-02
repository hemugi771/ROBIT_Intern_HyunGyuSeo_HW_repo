#include <stdio.h>

int main(void)
{
	float a, b, max, min, sum;
	printf("1번째 실수를 입력하시오. ");
	scanf_s("%f", &a);//첫 번째 실수만 입력하고 sum,  max, min값을 첫 번째 실수로 설정해준다
	sum = a;
	max = a;
	min = a;
	for (int i = 2; i < 6; i++)
	{
		printf("%d번째 실수를 입력하시오. ", i);
		scanf_s("%f", &b);//두 번째 실수부터는 입력받은 값과 원래 있던 값을 비교한다.
		max = (max > b) ? max : b;//전에 가장 큰 것과 비교해 큰 쪽이 max가 되고
		min = (min > b) ? b : min;//전에 가장 작은 것과 비교해 작은 쪽이 min이 된다.
		sum += b;//평균을 구하기 전에 이제까지 입력받았던 값들을 모두 더해준다
	}
	printf("평균은 %f입니다.\n최댓값은 %f입니다.\n최솟값은 %f입니다.", sum / 5, max, min);//평균, 최댓값, 최솟값을 출력한다
}