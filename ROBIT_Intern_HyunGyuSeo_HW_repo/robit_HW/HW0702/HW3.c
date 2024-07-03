#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int test(int a, char str[9]);

int main() {
	int play = 0;
	printf("음 입력\n");
	char str[9];
	scanf("%s", str);//문자열을 통해 음들을 입력 받음
	play = test(play, str);
	printf("\n결과 : ");
	switch (play) {//함수의 반환값을 통해 음의 종류를 판단
	case 1:
		printf("ascending");
		return 0;
	case 2:
		printf("descending");
		return 0;
	default:
		printf("mixed");
		return 0;
	}
}
int test(int a, char str[9]) {//str이 어떤 형태로 되어있는지 판별하는 함수
		if (str[0] == 'c'&& str[1] == 'd'&&str[2] == 'e'&& str[3] == 'f'&& str[4] == 'g'&& str[5] == 'a'&& str[6] == 'b'&&str[7] == 'C') { 
			return 1;//ascending
		}
		if (str[0] == 'C' && str[1] == 'b' && str[2] == 'a' && str[3] == 'g' && str[4] == 'f' && str[5] == 'e' && str[6] == 'd' && str[7] == 'c') {
			return 2;//descending
		}else {
			return 3;//mixed
		}
}