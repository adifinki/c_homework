#ifndef DEFINES_H
#define DEFINES_H
#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define FIRST_QUESTION 1
#define SECOND_QUESTION 2
#define THIRD_QUESTION 3

#define SUCCESS -2
#define FAIL 1

#define LEGAL_INPUT 1
#define ILEGAL_INPUT -1

#define DEFAULT 0					//this will be the default value of integer variables for initialization.
#define EMPTY 0						//THIS IS FOR THE RETURN VALUE OF ZERO IN SCANF.

#define MATRIX_TYPE_ERROR 1
#define MARIX_SHAPE_ERROR 2
#define MATRIX_ROWS 3
#define MATRIX_COULMNS 3

#define MAX_LENGTH 101
#define DOUBLE_MAX_LENGTH 201
#define DECIMAL_BASE 10
#define AMOOUNT_OF_ENGLISH_LETTERS 26
#define DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS  AMOOUNT_OF_ENGLISH_LETTERS*2

#define END_DIVIDER '\n'
#define ROW_DIVIDER '$'
#define COL_DIVIDER ' '
#define NEGATIVE '-'

#define MOST_FREQUENT 4

#define EX_2_NUMBER_OF_STATMENTS 2
#define EX_3_NUMBER_OF_STATMENTS 4

#define I_FLAG 'i'
#define I 0
#define N_FLAG 'n'
#define N 1
#define V_FLAG 'v'
#define V 2
#define X_FLAG 'x'
#define X 3
#define OPTIONS 4

#define NUMBER_TO_STR "first\0", "second\0", "third\0", "fourth\0"

#endif
