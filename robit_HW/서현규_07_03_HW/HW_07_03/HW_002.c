#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int ziphap[20] = {0, };//배열의 모든 값에 0을 넣음

int add(int x);
int remove(int x);
int check(int x);
int toggle(int x);
int all(int x);
int empty(int x);

int main() {
	int x;
	int size;
	char command[10];
	printf("연산을 선택하세요. (1 <= x <= 200\n");
	printf("add X\nremove X\n check X\ntoggle X\nall 0\nempty 0\n\n");
	while (1) {//무한 루프
		printf("input : ");
		scanf("%s %d", &command, &x);

		if (!strcmp(command, "add")) {//command를 입력한 값을 판정해서 함수를 실행하는 코드
			x = add(x);
		}
		if (!strcmp(command, "remove")) {
			x = remove(x);
		}
		if (!strcmp(command, "check")) {
			x = check(x);
		}
		if (!strcmp(command, "toggle")) {
			x = toggle(x);
		}
		if (!strcmp(command, "all")) {
			x = all(x);
		}
		if (!strcmp(command, "empty")) {
			x = empty(x);
		}

		printf("집합 : {");//출력
		for (int n = 0; n < 20; n++) {//x의 범위에 0은 포함되지 않는 것을 이용해서 0은 출력되지 않게 코드를 짬
			if (ziphap[n] != 0) {
				printf("%d, ", ziphap[n]);
			}
		}
		printf("}\n\n");
	}
}

int add(int x){//add함수
	for (int i = 0;i < 20;i++) {
		if (ziphap[i] == 0||ziphap[i]== x) {//집합에 빈칸이 있거나 x와 같은 값이 있다면
			ziphap[i] = x;//거기에다 x 덮어씌우고 탈출
			break;
		}
	}
}
int remove(int x){//remove함수
	for (int i = 0;i < 20;i++) {
		if (ziphap[i] == x) {//x와 같은 값이 있으면 없애기
			ziphap[i] = 0;
			for (int j = 0;j < i + 1;j++) {//그 뒤부터 배열의 모든 칸을 한 칸 당기기
				ziphap[i + j] = ziphap[i + j + 1];
				ziphap[i + j + 1] = 0;
			}
			break;
		}
	}
}
int check(int x){//check함수
	int i;//for문 밖에도 i를 써야해서 아예 따로 선언함
	for (i = 0;i < 20;i++) {
		if (ziphap[i] == x) {
			printf("1 ");//x와 같은 값이 있으면 1 출력하고 탈출
			break;
		}
	}
	if (i == 20) {//x와 같은 값이 없어서 for문이 최대로 반복했을 경우
		printf("0 ");
	}
}
int toggle(int x){//toggle함수
	for (int i = 0; i < 20; i++) {
		if (ziphap[i] == x) {
			ziphap[i] = 0;
			for (int j = 0;j < i + 1;j++) {
				ziphap[i + j] = ziphap[i + j + 1];
				ziphap[i + j + 1] = 0;
			}
			break;
		}
		else if (ziphap[i] == 0) {
			ziphap[i] = x;
			break;
		}
	}
}
int all(int x){//all함수
	for (int i = 0; i < 20; i++) {
		ziphap[i] = i+1;
	}
}
int empty(int x){//empty함수
	for (int i = 0; i < 20; i++) {
		ziphap[i] = 0;
	}
}