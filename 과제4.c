#include <stdio.h>

int main(void)
{
	printf("Input : ");
	float num1, num2, res;
	char i;
	scanf_s("%f %c %f", &num1, &i, &num2);
	switch (i) {
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
	printf("%.2f %c %.2f = %.2f",num1, i, num2, res);
}
