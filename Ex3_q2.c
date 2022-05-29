#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Ex3_q2.h"
#include "Defines.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*___________________declarations________________________*/
int zipped_validation(char zipped_str[]);
void create_statment(char* statment_number, char* target_array);
void print_statments_concatenation(char statments[][MAX_LENGTH], char concat[]);
int get_index_for_char(char character);
void print_max_characters(int* count_array, char* zipped_word);



int zipped_validation(char zipped_str[]) {
	//Return SUCCESS if the length of given string is long enough, FAIL otherwise
	return strlen(zipped_str) >= MOST_FREQUENT ? SUCCESS : FAIL;
}


void create_statment(char* statment_number, char* target_array) {
	/*
	* Get a statment and target_array from the user, and store thestatment as a atring in the target_array
	* @param statment_number: the number of current statment handeled for example: First/Second
	* @param target_array: pointer to the array that will store the statment
	*/
	printf("Please enter the %s statment.\n", statment_number);
	char letter = getchar();
	int i;
	for (i = 0; letter != '\n'; ++i) {
		target_array[i] = letter;
		letter = getchar();
	}
	target_array[i] = '\0';
}


void print_statments_concatenation(char statments[][MAX_LENGTH], char concat[]) {
	/*
	* Create concatenation of the statments, store it into array
	* @param statments: all the statments
	* @param concat: array for Concatenation
	*/
	strcpy(concat, statments[0]);  // Copy the string
	for (int i = 1; i < EX_2_NUMBER_OF_STATMENTS; i++)  // Going to happen 1 time if EX_2_NUMBER_OF_STATMENTS=2, but it's scalable for more statments
		strcat(concat, statments[i]);  //Concatenate the following string to the end of the first one
	printf("The concatenation result is:\n%s\n", concat); //Display the concatenated strings
}


int get_index_for_char(char character) {
	// Return a index for given character in alphabetic order where lower case get smaller index from uppercase
	if (isupper(character))
		return character - 'A' + AMOOUNT_OF_ENGLISH_LETTERS;
	return character - 'a';
}



void print_max_characters(int* count_array, char* zipped_word)
{
	/*
	* Get a string and counter array and prints the most frequent characters from the string according to count_array
	* @param count_array: counter of occurances inside a statment
	* @param zipped_word: union string of a given statment
	*/
	int printed_amount = 0;

	while (printed_amount < MOST_FREQUENT) {
		int max_value = 0;
		int index_list[DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS];
		// Get max value from array:
		for (int i = 0; i < DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS; ++i) {
			max_value = max_value < count_array[i] ? count_array[i] : max_value;
		}

		// Add indexes of max_values to index_list
		int max_counter = 0;
		for (int i = 0; i < DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS; ++i) {
			if (count_array[i] == max_value) {
				index_list[max_counter++] = i;
				count_array[i] = 0; // Avoiding to count the same max value more then once
			}
		}

		for (int i = 0; zipped_word[i] != '\0' && printed_amount < MOST_FREQUENT; ++i) {
			for (int j = 0; j < max_counter; j++) {
				if (get_index_for_char(zipped_word[i]) == index_list[j]) {
					printf("%c", zipped_word[i]);
					++printed_amount;
					continue;
				}
			}
		}
	}
	printf("\n");
}


int Magic_Words_Creator(){
	/*
	* Return FAIL if union statment length is too short, SUCCESS otherwise
	* Get two statments from the user and create its concatenation, union statment and new word including only top frequent characters.
	* 
	*/
	char statments_array[EX_2_NUMBER_OF_STATMENTS][MAX_LENGTH];
	char concat_statment[DOUBLE_MAX_LENGTH];  // target array  for the Concatenation
	int retval;

	char* number_to_str[] = { NUMBER_TO_STR };

	for (int i = 0; i < EX_2_NUMBER_OF_STATMENTS; ++i)
		create_statment(number_to_str[i], statments_array[i]);

	for (int i = 0; i < EX_2_NUMBER_OF_STATMENTS; ++i)
		printf("The %s statment is:\n%s\n", number_to_str[i], statments_array[i]);

	print_statments_concatenation(statments_array, concat_statment);
	int letters[DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS] = { 0 };
	char zipped_word[DOUBLE_AMOOUNT_OF_ENGLISH_LETTERS + 1] = { 0 };
	int j = 0;
	int char_index;
	for (int i = 0; concat_statment[i] != '\0'; ++i) {
		if (concat_statment[i] == ' ')
			continue;
		char_index = get_index_for_char(concat_statment[i]);
		if ((letters[char_index]) == 0) { //create zipped statment
			zipped_word[j++] = concat_statment[i];
		}
		letters[char_index]++;
	}
	retval = zipped_validation(zipped_word);
	if (retval != SUCCESS)
		return retval;
	printf("The first magic word is:\n");
	print_max_characters(letters, zipped_word);
	printf("The second magic word is:\n%s\n", zipped_word);
	return SUCCESS;
}
