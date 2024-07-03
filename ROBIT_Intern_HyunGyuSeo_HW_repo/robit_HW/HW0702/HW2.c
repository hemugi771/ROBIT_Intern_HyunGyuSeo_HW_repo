#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {
	int arr[8];
	printf("입력\n\n");
	for (int i = 0;i < 8;i++) {
		printf("%d : ", i);
		scanf("%d", &arr[i]);
		printf("\n");
	}
	int i = 7;
	while (i >= 0) {
		int max = 0;
		for (int l = 0;l < 8; l++) {
			printf("%d ", arr[l]);
		}//19번째 줄: 이미 정렬이 되었음에도 반복해서 출력되는 현상을 막기 위해 정렬이 되었으면 반복문을 나감
		if (arr[0] <= arr[1] && arr[1] <= arr[2] && arr[3] <= arr[4] && arr[4] <= arr[5] && arr[5] <= arr[6] && arr[6] <= arr[7]) { break; }
		for (int j = 0;j < i;j++) {// 가장 큰 값을 원래 max에다 넣기, 끝값을 원래 자리로 옮기기, max를 끝값에다 넣기
			if (arr[j] > arr[i]) {
				max = arr[j];
				arr[j] = arr[i];
				arr[i] = max;
			}
		}
		printf("\n");
		i--;
	}
	printf("\n출력\n\n");
	for (int l = 0;l < 8; l++) {
		printf("%d: %d\n", l, arr[l]);
	}
}