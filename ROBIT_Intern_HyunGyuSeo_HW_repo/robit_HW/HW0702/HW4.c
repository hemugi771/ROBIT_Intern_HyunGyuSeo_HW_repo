#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {//���ƾ��� �ٽ� ������ �߽��ϴ�
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
	for (int j = 0;j < N;j += 2) {//�κм��� ĭ��
		for (int l = N-j;l > 0;l-=2) {
		//l = N - j; //�κм��� ĭ���� Ž�� Ƚ��
			for (ind = 0; ind < j;ind++) {//�� �κм����� �迭�� ����, ũ�Ⱑ ���� �κм������� �迭�� ����Ƿ� �ݺ��� ������ �迭�� �ʱ�ȭ���� �ʾƵ� ��
				test[ind] = arr[j + ind];//test�� �ε��� ��°�� arr�� j + �ε��� ��°�� ä���ֱ�
			}
			for (int x = 0; x < ind;x++) {//�κм����� �������� ����
				for (int i = 0; i < ind - x - 1;i++) {
					if (test[i] > test[i + 1]) {
						t = test[i];
						test[i] = test[i + 1];
						test[i + 1] = t;
					}
					//j�� l�� ���� ���ؾ���
				}
				printf("j=%d, l=%d, x=%d, k=%d\n", j, l, x, k);
				for (int arrTest = 0; arrTest <= j;arrTest++) { printf("%d ", test[arrTest]); }printf("\n");//test[] �׽�Ʈ��
			}
			if (test[l / 2 + 1]==B) {//�߾Ӱ��� B�� ī��Ʈ(test�� �� ĭ¥���̸� ���� ���Ѵ�)
				k++;
			}
			if (l == 1 && test[0] == B) {//test�� �� ĭ¥���϶� �� ���� B�̸� ī��Ʈ
				k++;
			}
				
		}

	}
	printf("�߾Ӱ��� %d�� �κм����� ���� : %d", B, k);
}