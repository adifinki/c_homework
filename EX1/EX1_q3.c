#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

#define range ('z' - 'a' + 1)


int encryption(int i, char key, char* word)
{
	/*encrypt a letter, prints the encryption and returns the original letter*/
	char copy = word[i];
	word[i] = (char)('a' + ((int)word[i] - 'a' + ((int)key - ('a' - 1))) % range);
	if (i == 0)
		printf("Encryption is: %c", word[0]);
	else
		printf("%c", word[i]);
	return copy;
}

char decryption(int i, char key, char* word) /*decrypt a letter, prints it and returns the result*/
{ 
	word[i] = (char)('a' + (((int)word[i] - 'a' - ((int)key - ('a' - 1)) + range) % range));
	if (i == 0)
		printf("Decryption is: %c", word[0]);
	else
		printf("%c", word[i]);
	 return word[i];
}

int run(bool is_decryption, char key, char* word) {
	for (int i = 0; i < strlen(word); ++i)/*validate choise and activate the right function*/
	{
		if (word[i] < 97 || word[i]>122)
		{
			printf("\nError: input must be letters between a-z");
			return 1;
		}
		if (is_decryption) {
			key = decryption(i, key, word);
		}
		else {
			key = encryption(i, key, word);
		}
	}
	printf("\n");
	return 0;
}

int main()
{
	int choise;
	char word[1000];
	printf("Options:\n1. Encryption\n2. Decryption\nPlease specify the command:\n");
	scanf("%d", &choise);
	if (choise != 1 && choise != 2)
	{
		printf("Error: unknown command");
		return 1;
	}

	printf("Enter a string:\n");
	scanf("%s", word);
	return run(choise == 2, word[0], (word + sizeof(char)));
	}
