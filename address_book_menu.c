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
	for (int i=0; i<address_book->count;i++)
    {
        printf("Name: ");
        printf("%s", address_book->list[i].name);

        printf("\nPhone Numbers: \n");
        for(int j=0; j<PHONE_NUMBER_COUNT; j++)
        {
            if (strcmp(address_book->list[i].phone_numbers[j], "\0")==0 || (int)*address_book->list[i].phone_numbers[j]>=57 && (int)*address_book->list[i].phone_numbers[j]<= 48)
            {
                continue;
            }else{
                printf("\t%s\n", address_book->list[i].phone_numbers[j]);
            }
        }

        printf("\nEmail Addresses: \n");
        for(int k=0; k<EMAIL_ID_COUNT; k++)
        {
            if (strcmp(address_book->list[i].email_addresses[k], "\0")==0)
            {
                continue;
            }else{
                printf("\t%s\n", address_book->list[i].email_addresses[k]);
            }
        }

        printf("\nsi_no: %i\n\n", address_book->list[i].si_no);

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
