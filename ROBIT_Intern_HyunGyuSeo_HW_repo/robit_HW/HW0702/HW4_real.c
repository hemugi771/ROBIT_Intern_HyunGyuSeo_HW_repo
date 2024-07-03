/*
예를 들어서
5
3
1 2 3 4 5
이렇게 입력하면

1
2
3
4
5
123
234
345
12345

이렇게 탐색함
한 번 탐색할 때마다 새로운 배열을 만들어서 거기다 탐색한 값을 임시로 저장
새로 만든 배열을 오름차순으로 정렬 후 중간값이 B인지 판정

이럴라면
(부분수열 인덱스수 ) 0 0 0 0 0 2 2 2 4
(새로운 배열 채워진 인덱스)
0 1 2 3 4 012 123 234 01234
-> 반복할 때마다 처음에 입력받은 배열의 일부를 새 배열로 옮기기

(탐색 횟수) 0일때 N번, 부분수열 인덱스수가 증가할때마다 2씩 감소

정리하면
부분수열 인덱스수는 초기값 0에 2씩 증가, N 미만일때 실행
탐색횟수는 초기값 N에 2씩 감소(부분수열 인덱스수랑 같이 증감함)
{입력받은 배열의 부분수열 인덱스수만큼을 새로운 배열에다 옮김
새로운 배열의 부분수열 인덱스수만큼의 범위를 오름차순으로 정렬
중간값이 B이면 카운트 올림}

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {//공사중
	int N, B, ind, search, temp;
	printf("N : ");
	scanf("%d", &N);
	printf("B : ");
	scanf("%d", &B);//N이랑 B를 입력받음
	int arr[1000] = {0, };//입력받은 수열을 임시로 저장할 곳
	int test[1000] = {0, };//부분수열을 임시로 저장할 곳
	for (int i = 0;i < N;i++) {
		scanf("%d", &arr[i]);
	}
	search = N;//탐색횟수
	for (ind = 0; ind < N; ind += 2) {
		for (int rep = 0; rep < search; rep++){
			for (int a = rep; a <= ind; a++) {//배열 옮기는 코드
			test[a] = arr[a+rep];
			}
			printf("rep:%d:\n", rep);//테스트
			for (int i = 0;i <= ind;i++) {//테스트
				printf("%d ", test[i]);
			}
			printf("\n");
		/*	for (int x = 0; x <= ind;x++) {//부분수열 오름차순 정렬하는 코드
				for (int i = 0; i < N - x - 1;i++) {
					if (test[i] > test[i + 1]) {
					temp = test[i];
					test[i] = test[i + 1];
					test[i + 1] = temp;
				}
			}
		}*/
		//(중간값 판단해서 카운트 올리는 코드)
		}
		search -= 2;
	}//탐색횟수 2씩 감소
}
