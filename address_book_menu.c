#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

extern Status save_file(AddressBook *address_book);

int get_option(int type, const char *msg)
{
	char option[10];
	char *ptr;
	int result = 0;
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */

	// Displays message
	printf("%s", msg);
	if(type != 0)
		scanf("%s", option);

	if(type == 2){
		result = (int)*option;
		if(result != 'Y' && result != 'N')
			return get_option(type, msg);

	}else if(type == 1){
		// Checks if value is of type int
		result = strtol(option, &ptr, 10);
		if(*ptr != '\0'){
			printf("Enter a valid input.\n");
			return get_option(type, msg);
		}
	}

	return result;
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
	//needs to cycle through the whole address book, printing the name and cycle-printing phone numbers and emails
	//print message

	AddressBook deAl = *address_book;
	ContactInfo innerList[] = *address_book->list;
	get_option(5, "N for next page, P for previous page, Q to quit...");
	
	for (int i =0; i<deAl.count-1; i++)
	{
		ContactInfo currentContact = innerList[i];

		//print contact name
		printf("Name: %s", currentContact.name);
		//print phone #'s
		printf("Phone Number(s):\n");
		for (int j=0; j<4; j++)
		{
			printf("\t%s\n", currentContact.phone_numbers[j]);
		}
		//print email addresses
		printf("Email Address(s):\n");
		for (int k=0; k<4; k++)
		{
			printf("\t%s\n", currentContact.email_addresses[k]);
		}
		//print si_no
		printf("%s's si_no: %i\n", currentContact.name, currentContact.si_no);


		//evaluate choices
		if (strcmp(get_option, 'Y') == 0)
		{
			return e_new_line;
		}
		if (strcmp(get_option, 'N') == 0)
		{
			return e_back;
		}
		if (strcmp(get_option, 'Q') == 0)
		{
			break;
		}
	}

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

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
				/* Add your implementation to call add_contacts function here */
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
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
}
