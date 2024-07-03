#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int min, max, count=0, nNumcnt = 0;
	int num[10000];
	printf("min :");
	scanf("%d", &min);
	printf("max :");
	scanf("%d", &max);

	for (int i = min; i <= max; i++) {//min부터 max 사이의 숫자 개수만큼 반복
		//min부터 max 사이의 숫자(i)들을 자연수(2부터 1씩 증가함)의 제곱으로 나눠 나머지가 0이 아니면 배열에다 집어넣고 카운트를 하는 코드
		for (int nNum = 2;nNum < max; nNum++) {
			if (i % (nNum * nNum) != 0) {//어떤 제곱수로 나눠 나머지가 모두 0이 아니었다면
				nNumcnt++;//그 횟수를 센다
				if (nNumcnt == max-2) {//모든 제곱수로 나눠 나머지가 0이 아니었다면
					num[count] = i;//제곱ㄴㄴ수이므로 배열에 넣고  count에 1만큼 더한다
					count++;
				}
			}
		}
		nNumcnt = 0;//다음 숫자를 판정하기 위해 제곱수로 나눠 나머지가 0이 아닌 횟수를 센 값을 초기화시켜준다
	}

	printf("제곱 ㄴㄴ수 : %d개\n", count);//카운트한 수와 배열을 출력한다
	for (int i = 0; i < count;i++) {
		printf("%d ", num[i]);
	}
	
}

