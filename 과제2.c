#include <stdio.h>

int main(void)
{
	int n, a=0, b=1, sum;
	printf("n의 값 입력: ");
	scanf_s("%d", &n);
	for (int i = 0; i < n-1; i++) {
		sum = a + b;
		a = b;
		b = sum;
	}
	printf("%d", a);
}