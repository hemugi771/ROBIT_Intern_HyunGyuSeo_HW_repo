#include <stdio.h>

int main(void)
{
	int a;
	printf("값을 입력하세요.");
	scanf_s("%d", &a);
	for (int i = 1; i < 2 * a; i++) {//세로줄
		for (int j = 1; j < 2 * a; j++) {//가로줄
			if (i < a+1){//세로줄 별 개수 많아짐(첫째 줄부터 가운데까지)
					if (j<=i||j>=2*a-i) {
						printf("*");
					}
					else {
						printf(" ");
					}
				}
			else {//세로줄 별 개수 줄어듦(가운데를 넘은 때부터 맨 끝까지)
					if (j<2*a-i||j>i) {
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
/*
11

1001
1111
1001

100001
110011
111111
110011
100001

*/