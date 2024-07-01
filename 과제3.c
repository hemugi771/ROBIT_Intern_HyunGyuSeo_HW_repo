#include <stdio.h>

int main(void)
{
	int year, a = 0;
	printf("³âµµ¸¦ ÀÔ·ÂÇÏ¼¼¿ä : ");
	scanf_s("%d", &year);
	if (year % 4 == 0) {
		a = 1;
		if (year % 100 == 0) {
			a = 0;
			if (year % 400 == 0)
			{
				a = 1;
			}
		}
	}
	if (a == 0) {
		printf("À±³â ¾Æ´Ô");
	}
	else{
		printf("À±³â");
	}
}