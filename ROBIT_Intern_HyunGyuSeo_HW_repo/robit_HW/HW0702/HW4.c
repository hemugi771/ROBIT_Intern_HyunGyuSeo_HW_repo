#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {//갈아엎고 다시 만들기로 했습니다
	int N, B, k=0, ind, t, l;
	printf("N : ");
	scanf("%d", &N);
	printf("B : ");
	scanf("%d", &B);
	int arr[1000] = {0, };
	int test[1000] = {0, };
	for (int i = 0;i < N;i++) {
		scanf("%d", &arr[i]);
	}
	for (int j = 0;j < N;j += 2) {//부분수열 칸수
		for (int l = N-j;l > 0;l-=2) {
		//l = N - j; //부분수열 칸수별 탐색 횟수
			for (ind = 0; ind < j;ind++) {//각 부분수열을 배열로 만듦, 크기가 작은 부분수열부터 배열로 만드므로 반복할 때마다 배열을 초기화하지 않아도 됨
				test[ind] = arr[j + ind];//test의 인덱스 번째를 arr의 j + 인덱스 번째로 채워넣기
			}
			for (int x = 0; x < ind;x++) {//부분수열을 오름차순 정렬
				for (int i = 0; i < ind - x - 1;i++) {
					if (test[i] > test[i + 1]) {
						t = test[i];
						test[i] = test[i + 1];
						test[i + 1] = t;
					}
					//j와 l은 같이 변해야함
				}
				printf("j=%d, l=%d, x=%d, k=%d\n", j, l, x, k);
				for (int arrTest = 0; arrTest <= j;arrTest++) { printf("%d ", test[arrTest]); }printf("\n");//test[] 테스트용
			}
			if (test[l / 2 + 1]==B) {//중앙값이 B면 카운트(test가 한 칸짜리이면 세지 못한다)
				k++;
			}
			if (l == 1 && test[0] == B) {//test가 한 칸짜리일때 그 값이 B이면 카운트
				k++;
			}
				
		}

	}
	printf("중앙값이 %d인 부분수열의 개수 : %d", B, k);
}