#include <stdio.h>

int main(void)
{
	int a;
	printf("값을 입력하세요.");
	scanf_s("%d", &a);
	for (int i = 1; i <= a; i++) {//세로줄
		for (int j = 1; j < 2 * a; j++) {//가로줄
			if (i == a) {//바닥
				printf("*");
			}
			else {//삼각형 몸통
				if (j==a-(i-1)||j==a+(i-1)) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");//한 줄이 끝나면 줄바꿈
	}
}