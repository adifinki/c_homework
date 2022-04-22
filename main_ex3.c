#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Ex3_q1.h"
#include "EX3_q2.h"
#include "Ex3_q3.h"
#include "Defines.h"


/*___________________declarations________________________*/
void Front_Page_Setter();
int Input_Error_Handler(int Users_Option, int ret_value);


/*___________________Main function________________________*/

int main()
{
	int User_Option = DEFAULT;
	int ret_value = DEFAULT; //this variable will recieve the scanf or functions return value.

	Front_Page_Setter();  //setting the screen for the user.
	printf("Your choise is: ");
	ret_value = scanf("%d", &User_Option); //getting the users option.
	getchar(); // the \n of the scan
	
	switch (User_Option)
	{
		case FIRST_QUESTION:
			ret_value = Input_Error_Handler(User_Option, Matrix_Multiplicator());                          //First Question.
			break;
		case SECOND_QUESTION:
			ret_value = Input_Error_Handler(User_Option, Magic_Words_Creator());						//Second Question.
			break;
		case THIRD_QUESTION:
			ret_value = Input_Error_Handler(User_Option, small_grep());									//Third Question.
			break;
		default:
			ret_value = Input_Error_Handler(User_Option, EMPTY);
			break;
	}
	if (ret_value == SUCCESS)
		printf("Enjoy... :)\n");
	return ret_value;
}

/*___________________difinitions________________________*/

void Front_Page_Setter()
{
	printf("#####################################\n");
	printf("############ HOME WORK 3 ############\n");
	printf("#####################################\n\n");
	printf("Please enter the quesion's number:\n");
	printf("For matrix multiplicator enter 1.\n");
	printf("For magic words creator enter 2.\n");
	printf("For small grep function enter 3.\n");
}

void first_question_errors_handler(int ret_value) {
	switch (ret_value) {
		case MARIX_SHAPE_ERROR:
			printf("Expected %d * %d Matrix\n", MATRIX_ROWS, MATRIX_COULMNS);
			break;
		case MATRIX_TYPE_ERROR:
			printf("Error, you can enter just integers.\n");
			break;
	}
}

int Input_Error_Handler(int Users_Option, int ret_value)
{
	if (ret_value == SUCCESS)
		return SUCCESS;
	if (ret_value == EMPTY)
	{
		printf("You have intered an ilegal input.\n");			//scanf didn't get the wright input format.
	}
	else {
		switch (Users_Option) {
			case FIRST_QUESTION:																	//legal input.
				first_question_errors_handler(ret_value);
				break;
			case SECOND_QUESTION:
			case THIRD_QUESTION:
			default:																				//illegal input.
				printf("You have intered an ilegal input.\n");
				break;
			}
	}
	printf("Please try again later.\a\n");
	return ILEGAL_INPUT;
}
