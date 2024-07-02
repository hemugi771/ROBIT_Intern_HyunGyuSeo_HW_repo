#include <stdio.h>

int main(void)
{
	unsigned int n, a=0, b=1, sum; //배운 것 중에 가장 양수 범위가 넓은 자료형인 unsigned int를 사용하여 가능한 한 n이 커질 수 있도록 했다.
	printf("n 입력: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n-1; i++) {
		sum = a + b;//a와 b를 더한 값을 sum에다 저장해준 후 b의 값을 a로, 더했던 값을 b로 옮겼다.
		a = b;
		b = sum;
	}
	printf("n번째 피보나치 값: %d", a);//n-1번 반복하면 a의 값이 n번째 피보나치 값이 된다.
}