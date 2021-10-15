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
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("cls");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
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

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

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
				/* Add your implementation to call list_contacts function here */
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

	printf("0. Name\n");
	printf("1. Phone Number\n");
	printf("2. Email Address\n");
	printf("3. si Number\n");
	printf("4. Exit\n");
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

void printContact(AddressBook *address_book, int *indexes, int size){
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

Status add_contacts(AddressBook *address_book)
{
	int exit = -1;
	int i = 1;
	
	int addressBookSize = sizeof(ContactInfo) * address_book->count;
    ContactInfo *matchPtr = address_book->list;

	do
	{
		menu_header("Add Contact");
		printf("\n");
		printf("0. Back\n");
		printf("1. Name      :%s\n", matchPtr->name[0]);
		printf("2. Phone No %d :%s\n", 1, matchPtr->phone_numbers[0]);
		while (matchPtr->phone_numbers[i] != NULL && i < PHONE_NUMBER_COUNT)
		{
	        printf("            %d : %s\n", (i+1), matchPtr->phone_numbers[i]);
            i++;
		}
		printf("3. Email ID %d :%s\n", 1, matchPtr->email_addresses[0]);
		while (matchPtr->email_addresses[i] != NULL && i < EMAIL_ID_COUNT)
		{
	        printf("            %d : %s\n", (i+1), matchPtr->email_addresses[i]);
            i++;
        }
		
		int option = get_option(NUM, "Please select an option:\n");
		scanf("%d", option);

		switch(option)
		{
			case e_first_opt:
				exit = 0;
				break;
			case e_second_opt:
				printf("Enter the name:\n");
				scanf("%s", matchPtr->name[0]);
				break;
			case e_third_opt:
				printf("Enter Phone Number %d:\n", i);
				scanf("%s", matchPtr->phone_numbers[0]);
				break;
			case e_fourth_opt:
				printf("Enter Email ID %d:\n", i);
				scanf("%s", matchPtr->email_addresses[0]);
				break;
		}



	} while (exit != 0);

	address_book->count ++;
	return e_success;
	
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	FILE *fptr;
	if((fptr == fopen(address_book, "r"))== NULL)
	{
		FILE_ERROR(address_book);
		exit(4);
	}
	int addressBookSize = sizeof(ContactInfo) * address_book->count;
	char *nameE;
	char *phoneE[NUMBER_LEN];
	char *emailE[EMAIL_ID_LEN];
	int snE;
	int indexE;
	int option; 
	int counter = 0;
	do
	{
		contactMenu("Search by...");
		option = get_option(NUM, "");
		ContactInfo *matchPtr = address_book->list;
		switch(option)
		{
			case e_first_opt:
				printf("Enter a name to search: ");
				scanf("%s", nameE);
				while (fread(&address_book, sizeof(address_book),1, fptr)==1)
				{
					if(!strcmp(nameE, &address_book))
					{
						printf("contact FOUND\nName    : %s\nPhone No: %s\nEmail Id: %s\n", nameE, &phoneE , &emailE);
						counter++;
					}
				}
				if (!counter)
				{
					printf("Contanct not found\n");
					return -2;
				}
				else if (counter > 1)
				{
					printf("WARNING: contacts with either same NAME, PHONE NUMBER, or EMAIL ID found\n");
				}
				break;
			case e_second_opt:
				printf("Enter a phone number to search: ");
				scanf("%s", phoneE);
				while (fread(&address_book, sizeof(address_book), 1, fptr) == 1)
				{
					if(!strcmp(phoneE, &address_book))
					{
						printf("contact FOUND\nName    : %s\nPhone No: %s\nEmail Id: %s\n", nameE, &phoneE , &emailE);
						counter++;
					}
				}
				if (!counter)
				{
					printf("Contanct not found\n");
					return -2;
				}
				else if (counter > 1)
				{
					printf("WARNING: contacts with either same NAME, PHONE NUMBER, or EMAIL ID found\n");
				}
				break;
			case e_third_opt:
				printf("Enter an Email ID to search: ");
				scanf("%s", emailE);
				while (fread(&address_book, sizeof(address_book), 1, fptr) == 1);
				{
					if(!strcmp(emailE, &address_book))
					{
						printf("contact FOUND\nName    : %s\nPhone No: %s\nEmail Id: %s\n", nameE, &phoneE , &emailE);
						counter++;
					}
				}
				if (!counter)
				{
					printf("Contanct not found\n");
					return -2;
				}
				else if (counter > 1)
				{
					printf("WARNING: contacts with either same NAME, PHONE NUMBER, or EMAIL ID found\n");
				}
				break;
			case e_fourth_opt:
				printf("Enter an SI number to search: ");
				scanf("%s", NUM);
				while (fread(&address_book, sizeof(address_book), 1, fptr) == 1);
				{
					if(!strcmp(NUM, &address_book))
					{
						printf("contact FOUND\nName    : %s\nPhone No: %s\nEmail Id: %s\n", nameE, &phoneE , &emailE);
						counter++;
					}
				}
				if (!counter)
				{
					printf("Contanct not found\n");
					return -2;
				}
				else if (counter > 1)
				{
					printf("WARNING: contacts with either same NAME, PHONE NUMBER, or EMAIL ID found\n");
				}
				break;
			case e_fifth_opt:
				printf("\nNow exiting search contact...");
				return e_success;
		}
	} 
	while (option != e_fifth_opt);
	return e_success;
	
}

Status edit_contact(AddressBook *address_book)
{
    char *nameE;
	char *phoneE[NUMBER_LEN];
	char *emailE[EMAIL_ID_LEN];
	int snE;
    int indexE;
    int exit = -1;
    int option;
    
    /*search_contact(address_book);*/

    char select = get_option(CHAR,"\nPress: [s] = Select, [q] | Cancel: ");

    // review user input for next step
    if ( select == 'q' )
        return e_back;
    else if ( select != 's' )
        return e_no_match;

    snE = get_option(NUM,"Select a Serial Number (S.No) to Edit: ");

    
    int addressBookSize = sizeof(ContactInfo) * address_book->count;
    ContactInfo *matchPtr = address_book->list;
    matchPtr = searchBySiNum(matchPtr, addressBookSize, snE);
    
    do{
        menu_header("Edit Contact:");
	    printf("\n");
        printf("0. Back\n");
	    printf("1. Name       : %s\n", matchPtr->name[0]);
	    printf("2. Phone No %d : %s\n", 1, matchPtr->phone_numbers[0]);
        int i = 1;
        while (matchPtr->phone_numbers[i] != NULL && i < PHONE_NUMBER_COUNT){
	        printf("            %d : %s\n", (i+1), matchPtr->phone_numbers[i]);
            i++;
        }
	    printf("3. Email ID %d : %s\n", 1, matchPtr->email_addresses[0]);
        while (matchPtr->email_addresses[i] != NULL && i < EMAIL_ID_COUNT){
	        printf("            %d : %s\n", (i+1), matchPtr->email_addresses[i]);
            i++;
        }

        option = get_option(NUM, "\nPlease select an option: ");

        
        switch (option){
            case e_first_opt:
                exit = 0;
            case e_second_opt:
                printf("Enter Name: [Just enter removes the entry]: ");
                scanf("%s", nameE);
                strcpy(matchPtr->name[0], nameE);
            case e_third_opt:
                while (!(indexE<=5 || indexE>=1)){
                    printf("Enter Phone Number index to be change [Max 5]: ");
                    scanf("%d", &indexE);
                }
                printf("Enter Phone Number %d: [Just enter removes the entry]: ", indexE);
                scanf("%s", phoneE[indexE]);
                strcpy(matchPtr->phone_numbers[indexE], phoneE[indexE]);
            case e_fourth_opt:
                while (!(indexE<=5 || indexE>=1)){
                    printf("Enter Email Address index to be change [Max 5]: ");
                    scanf("%d", &indexE);
                }
                printf("Enter Email Address %d: [Just enter removes the entry]: ", indexE);
                scanf("%s", emailE[indexE]);
                strcpy(matchPtr->email_addresses[indexE], emailE[indexE]);
        }

    } while (exit != 0);

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
	system("cls");
	int option, siNum;
	int size = address_book->count;
	char input[32];
	char *check;
	int indexArray[address_book->count];
	int addressBookSize = sizeof(ContactInfo) * size;

		contactMenu("Delete by...");

		option = get_option(NUM, "");
		ContactInfo *matchPtr = address_book->list;
		
		system("cls");
		switch(option){
			case e_first_opt:
				get_string("name",input);
				break;
			case e_second_opt:
				get_string("phone number", input);
				break;
			case e_third_opt:
				get_string("email address", input);
				break;
			case e_fourth_opt:
				siNum = get_option(NUM, "Enter serial number\n");
				break;
			case e_fifth_opt:
				printf("Now exiting delete_contact...");
				return e_success;
		}
		
		int counter = 0;

		for(int index = 0; index < size; index++){
			switch (option)
			{
				case e_first_opt:
					matchPtr = searchByName(&matchPtr[index], addressBookSize, input);
					break;
				case e_second_opt:
					matchPtr = searchByPhNum(&matchPtr[index], addressBookSize, input);
					break;
				case e_third_opt:
					matchPtr = searchByEmail(&matchPtr[index], addressBookSize, input);
					break;
				case e_fourth_opt:
					matchPtr = searchBySiNum(&matchPtr[index], addressBookSize, siNum);
					break;
				default:
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
			system("cls");
			printContact(address_book, indexArray, counter);
			option = get_option(NUM, "Select which contact you would like to delete: \n(Input any other number to void deletion)\n");
			if(option < counter && option >= 0)
				excludeContact(address_book, indexArray[option]);
		}

	return e_success;

}
