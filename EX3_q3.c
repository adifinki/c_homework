#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Ex3_q3.h"
#include "Defines.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_statment(const char* number_of_statment, char target_array[]);
int get_flag_index(char flag);
int statment_to_switches(int switch_flag[], char* word);
void tolower_string(char* string);
void print_statment_with_word(char* statment, int switch_flag[], char word_to_find[], int index);



int get_statment(const char* number_of_statment, char target_array[]) {
	/*
	* Get a statment from the user, and store it in the target_array
	* @param number_of_statement: the number of the current statment handeled for example: first/second
	* @param target_array: pointer to the array that will store the statment (the result)
	*/
	printf("Please enter the %s statment.\n", number_of_statment);
	char letter = getchar();
	int i = 0;
	while (letter != '\n') {
		target_array[i++] = letter;
		letter = getchar();
	}
	if (i == 0)  // Empty statement
		return ILEGAL_INPUT;
	target_array[i] = '\0';
	return SUCCESS;
}

int get_flag_index(char flag) {
	/*
	* Return the switch's index for the switches array
	* Return ILEGAL_INPUT in case of invalid switch
	* @param: flag as the switch
	*/
	switch (flag) {
		case I_FLAG:
			return I;
		case N_FLAG:
			return N;
		case V_FLAG:
			return V;
		case X_FLAG:
			return X;
		default:
			return ILEGAL_INPUT;
	}
}

	int statment_to_switches(int switch_flag[], char* word) {
		/*
		* Return SUCCESS and add the statment into word and TRUE/FALSE to switch_flag
		* Reruen FAIL in case of invalid switch
		* @param: switch_flag contain ehich switches
		* @param: word as pointer to the word we want to find in the statment
		*/
		printf("Please enter the last statment.\n");
		char letter = getchar();
		int i = 0;
		while (letter != ' ' && letter != '\n') {
			word[i++] = letter;
			letter = getchar();
		}
		word[i] = '\0';
		int flag_index;
		while (letter != '\n') {
			letter = getchar();
			if (letter == '-') {
				flag_index = get_flag_index(getchar());
				if (flag_index == ILEGAL_INPUT)  // invalid switch
					return ILEGAL_INPUT;
				switch_flag[flag_index] = TRUE;
			}
		}
		if (switch_flag[V] && switch_flag[X])  // can't use -v and -x at the same time
			return ILEGAL_INPUT;
		return SUCCESS;
	}

	void tolower_string(char* string) {
		// Convert string to lower case
		for (; *string; ++string) *string = tolower(*string);
	}

	void print_statment_with_word(char* statment, int switch_flag[], char word_to_find[], int index) {
		/*
		 * Print the statment if the conditions in switch_flag applied
		 */
		char temp_word[MAX_LENGTH];
		char temp_statment[MAX_LENGTH];
		strcpy(temp_word, word_to_find);
		strcpy(temp_statment, statment);

		if (switch_flag[I]) {
			tolower_string(temp_word);
			tolower_string(temp_statment);
		}

		if ((strstr(temp_statment, temp_word) == NULL) ^ switch_flag[V])
			return;

		if (switch_flag[X] && strcmp(temp_statment, temp_word))
			return;

		if (switch_flag[N])
			printf("%d. ", index+1);
		printf("%s\n", statment);
	}

int small_grep() {
	/*
	* Get four statments and a commant.
	* the command with be a word and some flags: '<word> <flags>'
	* The flag options are:
	*	-i: ignore the differance between big and small letters
	*	-n: print the statment's number at the beginning
	*	-x: print only the statment that are just the same word with no other words
	*	-v: print the statments the doe's not inclide the word
	* command example:
	*	word -i -n -v
	*/
	int retval;
	char word_to_find[MAX_LENGTH];
	char statments_array[EX_3_NUMBER_OF_STATMENTS][MAX_LENGTH];

	char* number_to_str[] = { NUMBER_TO_STR };

	for (int i = 0; i < EX_3_NUMBER_OF_STATMENTS; ++i) {
		retval = get_statment(number_to_str[i], statments_array[i]);
		if (retval != SUCCESS) return retval;
	}
	int switch_flag[OPTIONS] = { FALSE };
	retval = statment_to_switches(switch_flag, word_to_find);
	if (retval != SUCCESS) return retval;
	for(int i = 0; i < EX_3_NUMBER_OF_STATMENTS; ++i)
		print_statment_with_word(statments_array[i], switch_flag, word_to_find, i);
	return SUCCESS;
}
