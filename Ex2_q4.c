#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define SIZE_ARRAY 15
#define NUMBER_BASE 10
#define SUCCESS 0
#define ERROR -1

int length(int num) {
	// return the amount of digits the given number has
	int length_counter = 0;
	for (; num > 0; ++length_counter) //updates the counter and divide the number
		num /= NUMBER_BASE;
	return length_counter;
}

int fillArray(int arr[]) {
	/* 
	get an array, fills it using the user input and return the length of the longest integer
	return -1 if an error has accured
	*/
	int max = 0;
	char digit;
	printf("please enter %d numbers\n", SIZE_ARRAY);
	for (int i = 0; i < SIZE_ARRAY; ++i) {
		arr[i] = 0;
		digit = getchar();
		// error check:
		if (!isdigit(digit)) {
			printf("One or more numbers are missing, maybe you've used something other then one space as a devider?");
			return ERROR;
		}
		while (isdigit(digit)) { // calculate the number
			arr[i] = arr[i] * NUMBER_BASE + (digit - '0'); // minus '0' convert the char of digit to int
 			digit = getchar();
			// error check:
			if ((digit == 0 || digit == '\n') && i < (SIZE_ARRAY - 1)) {
				printf("One or more numbers are missing, you need to enter %d numbers!", SIZE_ARRAY);
				return ERROR;
			}
		}
		// error check:
		if (digit != ' ' && digit != 0 && digit != '\n') {
			printf("Divider must be one space (' '). don't try me!");
			return ERROR;
		}
		if (arr[i] > max)
			max = arr[i];
	}
	return length(max);
}

int getDigit(int num, int d) {
	// return the digit in the 'd' location from the right of num (d=1 for the first)
	return (num / (int)pow(NUMBER_BASE, d - 1) % NUMBER_BASE);
}

int MostCommomDigit(int arr[], int d) {
	// return the most common digit in the 'd' location from the array (d=1 for the first)
	int count[NUMBER_BASE] = {0};
	for (int i = 0; i < SIZE_ARRAY; ++i) {
		count[getDigit(arr[i], d)] += 1;
	}
	int max = -1, max_i = -1;
	for (int i = 0; i < NUMBER_BASE; ++i) {
		if(count[i] > max) {
			max = count[i];
			max_i = i;
		}
	}
	return max_i;
}

int main(void) {
	// returns a number which each digit is the most common digit of integer array the user inserted
	int numbers[SIZE_ARRAY];
	int max_length = fillArray(numbers);
	if (max_length == -1) return 1;  // error raised in fillArray
	int new_num = 0;
	for (int i = 0; i < max_length; ++i) {
		new_num += MostCommomDigit(numbers, i+1) * (int)pow(NUMBER_BASE, i);
	}
	printf("The number is: %d", new_num);
	return SUCCESS;
}
