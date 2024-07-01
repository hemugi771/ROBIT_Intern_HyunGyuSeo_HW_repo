#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	printf("Input : ");
	double num1, num2, res;
	char oper;
	scanf("%lf %c %lf", &num1, &oper, &num2);//띄어쓰기로 연산자와 숫자를 구분하여 입력받는다.
	switch (oper) {//연산자의 종류에 따라 덧셈,뺄셈,곱셈,나눗셈,거듭제곱을 진행한다.
	case '+':
		res = num1 + num2;
		break;
	case '-':
		res = num1 - num2;
		break;
	case '*':
		res = num1 * num2;
		break;
	case '/':
		if (num2 == 0) { break; }
		res = num1 / num2;
		break;
	default:
		res = 1;// ^ 양옆에 실수형이 올 수 없다 해서 직접 만들었어요
		for (int i = 0; i < num2; i++) {
			res *= num1;
		}
	}
	printf("%.2lf %c %.2lf = %.2lf",num1, oper, num2, res);//문제의 예시처럼 소수점 두번째 자리까지 나타내게 하였다
}
