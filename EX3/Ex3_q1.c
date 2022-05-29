#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Ex3_q1.h"
#include "Defines.h"
#include <stdio.h>
#include <ctype.h>

/*___________________declarations________________________*/
int get_number(int* result, char expected_divider);
int Get_Matrix(int result_mat[][MATRIX_COULMNS], char matrix_num[]);
int multiplicator(int matrix_a[][MATRIX_COULMNS], int matrix_b[][MATRIX_COULMNS], int row, int col);


int get_number(int* result, char expected_divider) {
	/*
	* Return SUCCESS if no error was raised, and MATRIX_TYPE_ERROR if there was a type error.
	* Change *result to the input number.
	* @param int* result: Pointer to a result for the input number.
	* @param char expected_divider: The expected devider after the input (for validation).
	*/
	int is_negative = FALSE;
	int number = 0;
	char character;

	character = getchar();

	if (character == NEGATIVE) {
		is_negative = TRUE;

		character = getchar();
		if (!isdigit(character))
			return MATRIX_TYPE_ERROR;
	}

	while (isdigit(character))
	{
		number = number * DECIMAL_BASE + (character - '0');
		character = getchar();
	}

	if (character != expected_divider)
		return MATRIX_TYPE_ERROR;

	*result = is_negative ? -1 * number : number;
	return SUCCESS;
}

int Get_Matrix(int result_mat[][MATRIX_COULMNS], char matrix_num[]) {
	/*
	* Return SUCCESS if no error was raised,
	* MATRIX_TYPE_ERROR if there was a type error,
	* MARIX_SHAPE_ERROR if the matrix shape is invalid.
	* Change result_mat to the input number.
	* @param result_mat: The reult matrix.
	* @param matrix_num: The matrix number. for example, First or Second.
	*/
	printf("Please enter the %s matrix.\n", matrix_num);
	char character;
	for (int i = 0; i < MATRIX_ROWS * MATRIX_COULMNS; ++i) {
		int col = i % MATRIX_ROWS;
		int row = i / MATRIX_ROWS;
		char divider = COL_DIVIDER;
		if (i == (MATRIX_ROWS * MATRIX_COULMNS - 1))
			divider = END_DIVIDER;


		int return_value = get_number(&result_mat[row][col], divider);
		if (return_value != SUCCESS)
			return return_value;

		// check that $ was not missing but not in the end of the matrix
		if (col == MATRIX_COULMNS - 1 && divider != END_DIVIDER) {
			character = getchar();
			if (character != ROW_DIVIDER)
				return MARIX_SHAPE_ERROR;
			character = getchar();
			if (character != COL_DIVIDER)
				return MATRIX_TYPE_ERROR;
		}
	}
	return SUCCESS;
}

int multiplicator(int matrix_a[][MATRIX_COULMNS], int matrix_b[][MATRIX_COULMNS], int row, int col) {
	/*
	* Return the row and col matrix multiplactor
	* @param int matrix_a[][]: The first matrix.
	* @param int matrix_b[][]: The second matrix.
	* @param int row: The current row.
	* @param int col: The current col.
	*/
	int sum = 0;
	for (int i = 0; i < MATRIX_ROWS; ++i) {
		sum += matrix_a[row][i] * matrix_b[i][col];
	}
	return sum;
}


int Matrix_Multiplicator()
{
	/*
	* Get 2 matrixs, multiply them and print
	*/
	int matrix_a[MATRIX_ROWS][MATRIX_COULMNS];
	int matrix_b[MATRIX_ROWS][MATRIX_COULMNS];

	int ret_value;

	ret_value = Get_Matrix(matrix_a, "first");

	if (ret_value != SUCCESS)
		return ret_value;

	ret_value = Get_Matrix(matrix_b, "second");

	if (ret_value != SUCCESS)
		return ret_value;
	
	printf("The multiplication result is:\n");
	for (int i = 0; i < MATRIX_ROWS; ++i) {
		for (int j = 0; j < MATRIX_COULMNS; ++j) {
			printf("%d ", multiplicator(matrix_a, matrix_b, i, j));
		}
		printf("\n");
	}

	return SUCCESS;
}

