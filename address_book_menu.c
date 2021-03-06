#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"
#include "funct_by_call.h"


Status save_file(AddressBook *address_book);

/**
 * Takes type of return data desired and custom message
 * Takes user input and returns desired input
*/
int get_option(int type, const char *msg)
{
	char option[32];
	char *ptr;
	int result = 0;

	// Displays message
	printf("%s", msg);
	if(type != NONE)
		scanf("%s", option);

	if(type == CHAR){
		result = (int)*option;
	}else if(type == NUM){
		// Checks if value is of type int
		result = strtol(option, &ptr, 10);
		if(*ptr != '\0'){
			printf("Enter a valid input.\n");
			return get_option(type, msg);
		}
	}

	return result;
}


void static printPHandEMAIL(AddressBook *address_book, int index){
	ContactInfo *ptr = address_book->list;
	int counter = 0;
	int check;
	char str[32];
	printf("PhoneNumbers:\n");
	while(counter < PHONE_NUMBER_COUNT){
		check = strcmp(ptr[index].phone_numbers[counter], "");
		if(check != 0)
			printf("                 %s\n", ptr[index].phone_numbers[counter]);
		else
			break;
		counter++;
	}
	counter = 0;
	printf("Email Addresses:\n");
	while(counter < EMAIL_ID_COUNT){
		check = strcmp(ptr[index].email_addresses[counter], "");
		if(check != 0)
			printf("                 %s\n", ptr[index].email_addresses[counter]);
		else
			break;
		counter++;
	}

}

void printContacts(AddressBook *address_book, int *indexes, int size){
	//system("cls");
	int index;
	ContactInfo *ptr = address_book->list;
	for(int i = 0; i < size; i++){
		index = indexes[i];
		printf("Contact #%d\n", i);
		printf("**********************************\n");
		printf("Name:            %s\n", ptr[index].name);
		printPHandEMAIL(address_book, index);
		printf("Serial Number:   %d\n", ptr[index].si_no);
		printf("**********************************\n");
	}
}
void printContact(AddressBook *address_book, int index){
	system("cls");
	ContactInfo *ptr = address_book->list;

	printf("**********************************\n");
	printf("Name:            %s\n", ptr[index].name);
	printPHandEMAIL(address_book, index);
	printf("Serial Number:   %d\n", ptr[index].si_no);
	printf("**********************************\n");
}

void get_string(const char *type, char result[32]){
	printf("Enter %s\n", type);
	printf("(Only first 32 chars will be taken)\n");
	char input[100];
	scanf("%s", input);

	for(int i = 0;i < 32;i++){
		result[i] = input[i];
	}
	
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	printf("######### %s #######\n", title);
	printf("%s", msg);
	char option;
	int size = address_book->count;
	
	int indexOfInfo;
	ContactInfo *ptr = address_book->list;
	for(int i = 0; i < size; i++){
		indexOfInfo = index[i];
		printf("Contact #%d\n", i);
		printf("**********************************\n");
		printf("Name:            %s\n", ptr[indexOfInfo].name);
		printPHandEMAIL(address_book, indexOfInfo);
		printf("Serial Number:   %d\n", ptr[indexOfInfo].si_no);
		printf("**********************************\n");

		option = get_option(CHAR, "Enter 'n' to exit (any other input lists next iteration): ");
		if(option == 'n')
			break;
	}

	if(option != 'n')
		get_option(CHAR, "Enter any input to exit: ");

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	system("cls");
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

void indexArray(AddressBook *address_book, int *array){
	int count = address_book->count;

	array = realloc(array, address_book->count * sizeof(int));

	for(int i = 0; i < count; i++){
		array[i] = i;
		printf("array at %d is: %d\n", i, array[i]);
		printf("Name is %s\n", address_book->list[i]);
	}
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;
	int *count = calloc(address_book->count, sizeof(int));
	for(int i = 0; i < address_book->count; i++)
		count[i] = i;
	int index = address_book->count - 1;
	
	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		
		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				indexArray(address_book, count);
				list_contacts(address_book, "Listing Contacts...", count, "", e_list);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

void contactMenu(const char *msg){

	menu_header(msg);

	printf("0. Exit\n");
	printf("1. Name\n");
	printf("2. Phone Number\n");
	printf("3. Email Address\n");
	printf("4. Serial Number\n");
}

void changingContactVal(AddressBook *address_book, int index){
	int option, si_num, number;
	char input[32];
	short phoneIndex;
	short emailIndex; 
	do
	{	
		contactMenu("Edit the contact by");
		option = get_option(NUM, "");

		switch(option)
		{
			case e_first_opt:
				break;
			case e_second_opt:
				get_string("name", input);
				strcpy(address_book->list[index].name[0], input);
				break;
			case e_third_opt:
				phoneIndex = get_option(NUM, "Which phone do you want to edit? (0-4)");
				if(phoneIndex >-1 && phoneIndex < 5){
					get_string("phone number", input);
					strcpy(address_book->list[index].phone_numbers[phoneIndex], input);
				}else
					continue;
				break;
			case e_fourth_opt:
				emailIndex = get_option(NUM, "Which email do you want to edit? (0-4)");
				get_string("email address", input);
				strcpy(address_book->list[index].email_addresses[emailIndex], input);
				break;
			case e_fifth_opt:
				si_num = get_option(NUM, "Enter serial number: ");
				address_book->list[index].si_no = si_num;
				break;
			default:
				printf("Input a valid option!\n");
				break;
		}
		
		if(option != e_first_opt)
			printContact(address_book, index);

	} while (option != e_first_opt);
}

Status add_contacts(AddressBook *address_book)
{
	system("cls");
	ContactInfo *ptr;
	int count = address_book->count;
	ptr = realloc(ptr, (count + 1) * (sizeof(ContactInfo)));
	int option, si_num;
	char input[32];
	short phoneIndex = 0;
	short emailIndex = 0;
	short counter = 0;

	// Initializes list elements
	strcpy(address_book->list[count].name[0], "");
	for(int i = 0; i < PHONE_NUMBER_COUNT; i++){
		strcpy(address_book->list[count].phone_numbers[i], "");
		strcpy(address_book->list[count].email_addresses[i], "");
	}
	
	address_book->list[count].si_no = 0;
	contactMenu("add contact by..");
	

	do
	{	
		option = get_option(NUM, "");

		switch(option)
		{
			case e_first_opt:
				break;
			case e_second_opt:
				get_string("name", input);
				strcpy(address_book->list[count].name[0], input);
				break;
			case e_third_opt:
				get_string("phone number", input);
				strcpy(address_book->list[count].phone_numbers[phoneIndex], input);
				printf("Phone number is: %s\n",address_book->list[count].phone_numbers[phoneIndex]);
				phoneIndex++;
				break;
			case e_fourth_opt:
				get_string("email address", input);
				strcpy(address_book->list[count].email_addresses[emailIndex], input);
				emailIndex++;
				break;
			case e_fifth_opt:
				si_num = get_option(NUM, "Enter serial number: ");
				address_book->list[count].si_no = si_num;
				break;
			default:
				printf("Input a valid option!\n");
				break;
		}
		
		if(option != e_first_opt){
			counter ++;
			printContact(address_book, count);
			contactMenu("select an option");
		}

	} while (option != e_first_opt);

	free(ptr);
	if(counter != 0)
		address_book->count ++;
	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	int number[50];
	int length = 0;

	switch (field)
	{
		case 0:
			for (int i = 0; i < loop_count; i++) {
				if (strcmp(str, address_book->list[i].name[0]) == 0) {
					number[length] = address_book->list[i].si_no;
					length++;
				}
			}
			break;
		case 1:
			for (int i = 0; i < loop_count; i++) {
				for (int j = 0; j < PHONE_NUMBER_COUNT; j++) {
					if (strcmp(str, address_book->list[i].phone_numbers[j]) == 0) {
						number[length] = address_book->list[i].si_no;
						length++;
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < loop_count; i++) {
				for (int j = 0; j < EMAIL_ID_COUNT; j++) {
					if (strcmp(str, address_book->list[i].email_addresses[j]) == 0) {
						number[length] = address_book->list[i].si_no;
						length++;
					}
				}
			}
			break;
		default:
			break;
	}
	list_contacts(address_book, "Search Result:", number, "", mode);
	return e_success;
}

Status search_contact(AddressBook *address_book)
{
	system("cls");
	ContactInfo *info = address_book->list;
	FILE *fp;
	char name[NAME_LEN];
	char phoneNum[NUMBER_LEN];
	char email[EMAIL_ID_LEN];
	int siNum;

	int size = address_book->count; // 6
	int indexArray[address_book->count];

	int counter = 0;

	int addressBookSize = sizeof(ContactInfo) * size; // 6

	int inputOption;
	do
	{
		printf("Search by ...\n");
		printf("0. Exit\n");
		printf("1. Name\n");
		printf("2. Phonenumber\n");
		printf("3. Email\n");


		inputOption = get_option(NUM, "Please select an option: ");

		switch (inputOption)
		{
			case e_first_opt:
				return e_back;
			case e_second_opt:
				printf("\nEnter the name you want to search: ");
				scanf("%s", name);

				for (int index = 0; index < size; index++)
				{
					info = searchByName(&info[index], addressBookSize, name);
					if (info != NULL)
					{
						indexArray[counter] = index;
						counter++;
					}
					else
					{
						info = address_book->list;
					}
				}
				if (counter == 0)
				{
					printf("\n\nNot found\n");
				}
				else
				{
					printContacts(address_book, indexArray, counter);
				}
				break;

			case e_third_opt:
				printf("\nEnter the phone number you want to search: ");
				scanf("%s", phoneNum);
				for (int index = 0; index < size; index++)
				{
					info = searchByPhNum(&info[index], addressBookSize, phoneNum);
					printf("%s", info);
					if (info != NULL)
					{
						indexArray[counter] = index;
						counter++;
					}
					else
					{
						info = address_book->list;
					}
				}
				if (counter == 0)
				{
					printf("\n\nNot found");
				}
				else
				{
					printContacts(address_book, indexArray, counter);
				}
				break;

			case e_fourth_opt:
				printf("\nEnter the Email ID you want to search: ");
				scanf("%s", email);
				for (int index = 0; index < size; index++)
				{
					info = searchByEmail(&info[index], addressBookSize, email);
					printf("%s", info);
					if (info != NULL)
					{
						indexArray[counter] = index;
						counter++;
					}
					else
					{
						info = address_book->list;
					}
				}
				if (counter == 0)
				{
					printf("\n\nNot found");
				}
				else
				{
					printContacts(address_book, indexArray, counter);
				}
				break;
			default:
				break;




		}

		counter = 0;
	} 
	while (inputOption != 0);
	return e_success;
}


Status edit_contact(AddressBook *address_book)
{
    ContactInfo *ptr;
	int option , siNum;
	int size = address_book->count;
	char input[32];
	int indexArray[size];
	int addressBookSize = sizeof(ContactInfo) * size;

	contactMenu("Edit contacts by... ");

	option = get_option(NUM, "");
	ContactInfo *matchPtr = address_book->list;

	switch(option){
		case e_first_opt:
			printf("Now exiting edit_contact...");
			return e_success;
		case e_second_opt:
			get_string("name",input);
			break;
		case e_third_opt:
			get_string("phone number", input);
			break;
		case e_fourth_opt:
			get_string("email address", input);
			break;
		case e_fifth_opt:
			siNum = get_option(NUM, "Enter serial number\n");
			break;
	}

	int counter = 0;

	// Checks all contacts for what the user would like to search for
	for(int index = 0; index < size; index++){
		switch (option)
		{
			case e_second_opt:
				matchPtr = searchByName(&matchPtr[index], addressBookSize, input);
				break;
			case e_third_opt:
				matchPtr = searchByPhNum(&matchPtr[index], addressBookSize, input);
				break;
			case e_fourth_opt:
				matchPtr = searchByEmail(&matchPtr[index], addressBookSize, input);
				break;
			case e_fifth_opt:
				matchPtr = searchBySiNum(&matchPtr[index], addressBookSize, siNum);
				break;
			}

		if(matchPtr != NULL){
			indexArray[counter] = index;
			counter++;
		}else
			matchPtr = address_book->list;
	}

	if(counter == 0){
		printf("Not found\n");
		return e_no_match;
	}
	else{
		printContacts(address_book, indexArray, counter);
		option = get_option(NUM, "Select which contact you would like to edit: \n(Input any other number to void deletion)\n");
		if(option < counter && option >= 0){
			changingContactVal(address_book, indexArray[option]);
		}
	}


	return e_success;
}

void excludeContact(AddressBook *address_book, int index){
	int size = address_book->count;
	ContactInfo ptr[size - 1];
	short found = 0;
	for(int i = 0; i < size - 1; i++){
		if(i == index)
			found = 1;
		if(found == 0)
			ptr[i] = address_book->list[i];
		else
			ptr[i] = address_book->list[i+1];
	}

	for(int i = 0; i < size - 1; i++)
		address_book->list[i] = ptr[i];

	address_book->count --;
}

Status delete_contact(AddressBook *address_book)
{	
	ContactInfo *ptr;
	int option, siNum;
	int size = address_book->count;
	char input[32];
	int indexArray[address_book->count];
	int addressBookSize = sizeof(ContactInfo) * size;

	contactMenu("Delete by...");

	option = get_option(NUM, "");
	ContactInfo *matchPtr = address_book->list;
		
	switch(option){
		case e_first_opt:
			printf("Now exiting delete_contact...");
			return e_success;
		case e_second_opt:
			get_string("name",input);
			break;
		case e_third_opt:
			get_string("phone number", input);
			break;
		case e_fourth_opt:
			get_string("email address", input);
			break;
		case e_fifth_opt:
			siNum = get_option(NUM, "Enter serial number\n");
			break;
	}
		
	int counter = 0;

	// Checks all contacts for what the user would like to search for
	for(int index = 0; index < size; index++){
		switch (option)
		{
			case e_second_opt:
				matchPtr = searchByName(&matchPtr[index], addressBookSize, input);
				break;
			case e_third_opt:
				matchPtr = searchByPhNum(&matchPtr[index], addressBookSize, input);
				break;
			case e_fourth_opt:
				matchPtr = searchByEmail(&matchPtr[index], addressBookSize, input);
				break;
			case e_fifth_opt:
				matchPtr = searchBySiNum(&matchPtr[index], addressBookSize, siNum);
				break;
			}

		if(matchPtr != NULL){
			indexArray[counter] = index;
			counter++;
		}else
			matchPtr = address_book->list;
	}

	if(counter == 0){
		printf("Not found\n");
		return e_no_match;
	}
	else{
		printContacts(address_book, indexArray, counter);
		option = get_option(NUM, "Select which contact you would like to delete: \n(Input any other number to void deletion)\n");
		if(option < counter && option >= 0)
			excludeContact(address_book, indexArray[option]);
	}
	return e_success;
}