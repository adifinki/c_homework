#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

int palindrom()
{
	int number;
	int reverse = 0;
	printf("Enter a number:\n");
	scanf("%d", &number);
	int copy = number;
	while (number > 0)
	{
		reverse = reverse * 10 + number % 10;
		number = number / 10;
	}
	if (copy == reverse)
		printf("%d is a palindrom", copy);
	else
		printf("%d isn't a palindrom", copy);
	return 0;
}

int main()
{
	palindrom();
}
