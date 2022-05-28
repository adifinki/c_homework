#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Ex4_q2_318863693.h"
#include "defines.h"

typedef struct {
	char* item_name;
	char* department;
	char* expiration_date;
	double price;
	int available;
} Item;

void get_date_from_str(int date[DATE_VALUES], char* str);
int compare_dates(char* first_date, char* second_date);
int allocate_str_field(char** target, char* source, int max_size);
int process_item(Item* item, char* item_str);
int get_items_str(char items_str[STORE_SIZE][MAX_ROW_LENGTH]);
void free_item(Item item);
void free_memory(Item* store_items, int size);
void get_item_str(Item item, char* result);
void print_inventory(Item* store_items, int size);
void swap_items(Item* one, Item* two);
void expedition_sort(Item* store_items, int size);
void price_sort(Item* store_items, int size);
int inventory_update(Item** store_items, int* size);


void get_date_from_str(int date[DATE_VALUES], char* str) {
	/*
	* get string date and parse it into array ["day","month","year"]
	* @param date: target array
	* @param str: source date
	*/
	char copy[EXPIRATION_DATE_STRING_LENGTH];
	strcpy(copy, str);
	char* ptr = strtok(copy, DATE_DELIMITER);
	for (int i = 0; i < DATE_VALUES && ptr != NULL; ++i) {
		date[i] = atoi(ptr);
		ptr = strtok(NULL, DATE_DELIMITER);
	}
}

int compare_dates(char* first_date, char* second_date) {
	/*
	* get two date strings and return BIGGER if the first date is after the second, 
	* SMALLER if the second date is after the first, SUCCESS if they are identical.
	* @param first_date: string of the first date
	* @param second_date: string of the second date
	*/
	int date1[DATE_VALUES] = { 0 };
	int date2[DATE_VALUES] = { 0 };

	get_date_from_str(date1, first_date);
	get_date_from_str(date2, second_date);

	for (int i = DATE_VALUES - 1; i >= 0; --i) {
		if (date1[i] == date2[i])
			continue;
		return date1[i] > date2[i] ? BIGGER : SMALLER;
	}
	return SUCCESS;
}

int allocate_str_field(char** target, char* source, int max_size) {
	/*
	* allocate memory for source string in the adress of target. return SUCCES if allocation succeded and FALSE if the source string is too long
	* @param target: adress for aloocation
	* @param source: the string data we want to save on target
	* @param max_size: the maximum size of the source string
	*/
	int size = strlen(source);
	if (max_size < size)
		return FAIL;
	*target = (char*)calloc(size+1, sizeof(char));
	if (target == NULL)
		return FAIL;
	memcpy(*target, source, size);
	return SUCCESS;
}

int process_item(Item* item, char* item_str) {
	/*
	* get string of an item and return SUCCESS after creating item struct or FAIL if the string did not include all fields
	* @param item: pointer to struct item whom will be initilaized
	* @param item_str: string that will be converted to item struct
	*/
	char* ptr = strtok(item_str, DELIMITER), *garbage;
	int counter = 0, res;
	while (ptr != NULL) {
		++counter;
		switch (counter) {
		case NAME:
			res = allocate_str_field(&item->item_name, ptr, ITEM_NAME_LENGTH);
			break;
		case DEPARTMENT:
			res = allocate_str_field(&item->department, ptr, DEPARTMENT_NAME_LENGTH);
			break;
		case DATE:
			res = allocate_str_field(&item->expiration_date, ptr, EXPIRATION_DATE_STRING_LENGTH);
			break;
		case PRICE:
			item->price = strtod(ptr, &garbage);
			break;
		case AVAILABLE:
			item->available = atoi(ptr);
			break;
		default:
			return FAIL;
		}
		if (res == FAIL)
			return FAIL;

		ptr = strtok(NULL, DELIMITER);
	}

	if (counter < STRUCT_FIELDS_NUMBER)
		return FAIL;
	
	return SUCCESS;
}

int get_items_str(char items_str[STORE_SIZE][MAX_ROW_LENGTH]) {
	/*
	* gets an array of strings, initilaize it with strings from the user and return the number of items in the array
	* @param items_str: array of strings to fill
	*/
	char input[MAX_ROW_LENGTH] = { 0 };
	for (int i = 0; i < STORE_SIZE; ++i) {
		char* retval = fgets(input, MAX_ROW_LENGTH, stdin);
		if (retval == NULL)
			return FAIL;
		input[strcspn(input, "\n")] = 0;
		if (strcmp(input, STOP) == 0) {
			return i;
		}
		strcpy(items_str[i], input);
	}
	return STORE_SIZE;
}

void free_item(Item item) {
	/*
	* free the allocated memory of a given item structure
	* @param item: item structer
	*/
	free(item.item_name);
	free(item.department);
	free(item.expiration_date);
}


void free_memory(Item* store_items, int size) {
	/*
	* free the allocated memory of a given store
	* @param store_items: a pointer to array of item structures
	* @param size: number of items in array of items
	*/
	for (int i = 0; i < size; ++i)
		free_item(store_items[i]);
	free(store_items);
}

void get_item_str(Item item, char* result) {
	/*
	*format an item struct into string
	* @param item: item structer
	* @param result: pointer to the formatted output
	*/
	sprintf(result, "%s"DELIMITER"%s"DELIMITER"%s"DELIMITER"%f"DELIMITER"%d\n", item.item_name, item.department, item.expiration_date, item.price, item.available);
}

void print_inventory(Item* store_items,int size) {
	/*
	*prints store inventory
	* @param store_items: array of item structers to print
	* @param size: number of structers
	*/
	char line[MAX_ROW_LENGTH];
	for (int i=0; i < size; ++i) {
		get_item_str(store_items[i], line);
		printf("%s", line);
	}
	printf("\n");
}

void swap_items(Item* one, Item* two) {
	/*
	*swap between two items in a store of items
	* @param one: struct item
	* @param two: struct item
	*/
	Item temp;
	temp.item_name = two->item_name;
	temp.department = two->department;
	temp.expiration_date = two->expiration_date;
	temp.price = two->price;
	temp.available = two->available;

	two->item_name = one->item_name;
	two->department = one->department;
	two->expiration_date = one->expiration_date;
	two->price = one->price;
	two->available = one->available;

	one->item_name = temp.item_name;
	one->department = temp.department;
	one->expiration_date = temp.expiration_date;
	one->price = temp.price;
	one->available = temp.available;
}


void expedition_sort(Item* store_items, int size) {
	/*
	*sorting a store by expedition dates of it's items
	* @param store_items: array of item structers to print
	* @param size: number of structers
	*/
	int smallest_index;
	for (int i = 0; i < size - 1; ++i) {
		smallest_index = i;
		for (int j = i + 1; j < size; ++j)
			if (compare_dates(store_items[smallest_index].expiration_date, store_items[j].expiration_date) == BIGGER)
				smallest_index = j;
		// swap everything until the smallest is the first.
		for (int j = smallest_index; j > i; --j)
			swap_items(&store_items[j], &store_items[j - 1]);
	}
}

void price_sort(Item* store_items, int size) {
	/*
	*sorting a store by prices of it's items
	* @param store_items: array of item structers to print
	* @param size: number of structers
	*/
	int smallest_index;
	for (int i = 0; i< size - 1 ; ++i) {
		smallest_index = i;
		for (int j = i + 1; j < size ; ++j)
			if (store_items[smallest_index].price > store_items[j].price)
				smallest_index = j;
		// swap everything until the smallest is the first.
		for (int j = smallest_index; j > i; --j)
			swap_items(&store_items[j], &store_items[j-1]);
	}
}

int inventory_update(Item** store_items, int* size) {
	/*
	*deleting expired items from a store
	* @param store_items: array of item structers to print
	* @param size: number of structers
	*/
	char date[MAX_ROW_LENGTH] = { 0 };
	printf("Please enter the present date.\n");
	char* retval = fgets(date, MAX_ROW_LENGTH, stdin);
	if (retval == NULL)
		return FAIL;
	date[strcspn(date, "\n")] = 0;

	Item* new_store = (Item*)malloc(STORE_SIZE * sizeof(*new_store));
	if (new_store == NULL)
		return FAIL;
	int count = 0;
	for (int i = 0; i < *size; ++i)
	{
		if (compare_dates((*store_items)[i].expiration_date, date) == SMALLER) {
			free_item((*store_items)[i]);
			continue;
		}

		char item_str[MAX_ROW_LENGTH];
		get_item_str((*store_items)[i], item_str);
		process_item(&new_store[count], item_str); 
		++count;
	}
	free(*store_items);
	*store_items = new_store;
	*size = count;
	printf("You have successfully removed all of the expired items from the inventory.\n\n");
	return SUCCESS;
}

int main(int argc, char* argv[]){
	printf(
		"### Welcome To Sience For Ice Creame Shop ###\n"
		"Please Enter up to 40 products.\n"
		"The items should be intered int the format below: \n"
		"item_name_*_department_*_expiration_date_*_price_*_available.\n"
		"The expiration_date should be in the formet: dd.mm.yyyy\n"
		"The price in Shekels should be in the formet: xx.yy\n\n"
		"In order to enyer less than 40 items just enter the string \"STOP\"\n\n"
	);
	char items_str[STORE_SIZE][MAX_ROW_LENGTH], choise[MAX_ROW_LENGTH];
	int size = get_items_str(items_str), res = SUCCESS, i = 0;
		

	Item* store_items = (Item*)malloc(STORE_SIZE * sizeof(*store_items));
	if (store_items == NULL)
		return FAIL;

	for (; i < size && res == SUCCESS; ++i) {
		res = process_item(&store_items[i], items_str[i]);
	}

	if (res == FAIL)
		size = i; // free only what we have allocated
	else {
		do {
			printf(
				"Please chose the operation for the automated system to do.\n"
				"Choose 1 in order to print the products in the store.\n"
				"Choose 2 in order to sort the inventory by the expiration date.\n"
				"Choose 3 in to sort the inventory by the price.\n"
				"Choose 4 in order to update the inventory after throwing the expired items.\n"
				"Choose 0 at any time in order to stop the program and display the final inventory.\n\n"
			);

			char* retval = fgets(choise, MAX_ROW_LENGTH, stdin);
			if (retval == NULL)
				return FAIL;
			choise[strcspn(choise, "\n")] = 0;

			switch (atoi(choise)) {
			case STOP_PROGRAM:
				printf("Thank you for visiting our store.\nHave a wonderful day.\n");
				break;
			case PRINT_PRODUCTS:
				printf("You chose to print the products in the store option.\n");
				print_inventory(store_items, size);
				break;
			case SORT_BY_DATE:
				printf("You chose to sort the inventory by the expiration date.\n");
				expedition_sort(store_items, size);
				print_inventory(store_items, size);
				break;
			case SORT_BY_PRICE:
				printf("You chose to sort the inventory by the price.\n");
				price_sort(store_items, size);
				print_inventory(store_items, size);
				break;
			case UPDATE:
				printf("You chose to get rid of all expires items in the inventory.\n");
				res = inventory_update(&store_items, &size);
				print_inventory(store_items, size);
				break;
			default:
				printf("%s bad choise\n\n", choise);
				break;
			}
			if (res == FAIL) {
				printf("An Error Has Occure!\n");
				break;
			}

		} while (atoi(choise) != STOP_PROGRAM);
	}


	free_memory(store_items, size);
	return res;

}
