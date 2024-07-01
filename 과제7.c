#include <stdio.h>

int main(void)
{
	int n, r, N = 1, R = 1, NR = 1, NR1 = 1, nr = 1;
	printf("n과 r 입력(띄어쓰기 구분) : ");
	scanf_s("%d%d", &n, &r);
	for (int i = n; i > 0; i--) {
		N *= i;//N = n!
	}
	for (int i = r; i > 0; i--) {
		R *= i;//R = r!
	}
	for (int i = n-r; i > 0; i--) {
		NR *= i;//NR = (n-r)!
	}
	for (int i = n+r-1; i > 0; i--) {
		NR1 *= i;//NR1 = (n+r-1)!
	}
	for (int i = 0; i < r; i++) {
		nr *= n;
	}
	printf("순열 = %d\n", N/NR);
	printf("중복순열 = %d\n", nr);
	printf("조합 = %d\n", N/(NR*R));
	printf("중복조합 = %d\n", NR1/(N*R/n));//n!/n = (n-1)!
}
