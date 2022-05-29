#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

int abs(int num)
{
	if (num < 0)
		return -1 * num;
	return num;
}


int astricks()
{
	int number = 0;
	for (int i = 0; ((i < 3) && (number % 2 == 0)); ++i)
	{
		if (i)
			printf("Input Error: the number must be odd\n");
		printf("please enter a number:\n");
		scanf("%d", &number);
	}

	if (number % 2 == 0)
	{
		printf("Input failed 3 times, exiting...\n");
		return 1;
	}
	int mid = (number / 2);
	for (int i = 0; i < number; ++i)
	{
		if (i == mid) /* handle the middle line: */
		{
			for (int j = 0; j < number; ++j)
				printf("*");
		}
		else /* handle the top side and the down side: */
		{
			int jump_between_ast = abs(mid-i) - 1; /* jumps between each asterisk */
			int spaces_num_begining = mid - abs(mid - i); /* spaces in the start of the line */

			printf("%*s", spaces_num_begining, "");
			/* print 3 asterisks each line with the calculated spaces between */
			for (int j = 0; j < 3; ++j)
			{
				printf("*");
				if (j < 2)
					printf("%*s", jump_between_ast, "");

			}
		}
		printf("\n");
	}
}

int main(void)
{
	astricks();
}
