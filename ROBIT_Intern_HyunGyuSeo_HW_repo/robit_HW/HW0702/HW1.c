#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int type1(int A);//각각의 타입별로 모양을 출력하는 함수 선언
int type2(int A);
int type3(int A);
int type4(int A);


int main() {
	int a, b;
	printf("사이즈와 종류를 입력하시오.");
	scanf("%d%d", &a, &b);
	switch (b) {//switch case문을 활용하여 입력받은 타입별로 알맞은 함수를 사용하도록 함
	case 1:
		a = type1(a);
	case 2:
		a = type2(a);
	case 3:
		a = type3(a);
	case 4:
		a = type4(a);
	}
}
int type1(int A){
	for (int i = 1; i <= A; i++) {//세로줄
		for (int j = 1; j <= A/2+1; j++) {//가로줄
			if (i<=A/2+1) {//첫째 줄부터 가운데까지
				if (j<=i) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {//가운데를 넘은 때부터 맨 끝까지
				if (j<=A-i+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");//한 줄이 끝나면 줄바꿈
	}
	return 0;
}

int type2(int A) {
	for (int i = 1; i <= A; i++) {//세로줄
		for (int j = 1; j <= A / 2 + 1; j++) {//가로줄
			if (i<=A/2+1) {//첫째 줄부터 가운데까지
				if (j>A/2-i+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {//가운데를 넘은 때부터 맨 끝까지
				if (j>=A/2-A+i+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");//한 줄이 끝나면 줄바꿈
	}
	return 0;
}

int type3(int A){
	for (int i = 1; i <= A; i++) {//세로줄
		for (int j = 1; j <= A; j++) {//가로줄
			if (i<=A/2+1) {//첫째 줄부터 가운데까지
				if (j>=i&&j<=A-i+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {//가운데를 넘은 때부터 맨 끝까지
				if (j<=i&&j>=A-i+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");//한 줄이 끝나면 줄바꿈
	}
	return 0;
}

int type4(int A) {
	for (int i = 1; i <= A; i++) {//세로줄
		for (int j = 1; j <= A; j++) {//가로줄
			if (i<=A/2+1) {//첫째 줄부터 가운데까지
				if (j>=i&&j<=A/2+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {//가운데를 넘은 때부터 맨 끝까지
				if (j<=i&&j>=A/2+1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");//한 줄이 끝나면 줄바꿈
	}
	return 0;
}