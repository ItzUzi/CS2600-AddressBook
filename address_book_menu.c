#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

Status save_file(AddressBook *address_book);

/**
 * Takes type of return data desired and custom message
 * Takes user input and returns desired input
 */
int get_option(int type, const char *msg)
{
	char option[10];
	char *ptr;
	int result = 0;

	// Displays message
	printf("%s", msg);
	if (type != 0)
		scanf("%s", option);

	if (type == 2)
	{
		result = (int)*option;
		if (result != 'Y' && result != 'N')
			return get_option(type, msg);
	}
	else if (type == 1)
	{
		// Checks if value is of type int
		result = strtol(option, &ptr, 10);
		if (*ptr != '\0')
		{
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

		if ((address_book->count == 0) && (option != e_add_contact))
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

void contactMenu(const char *msg)
{

	menu_header(msg);

	printf("0. Name\n");
	printf("1. Phone Number\n");
	printf("2. Email Address\n");
	printf("3. si Number\n");
	printf("4. Exit\n");
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
		contactMenu("Search Contact By:\n");

		inputOption = get_option(NUM, "\nPlease select an option: ");

		switch (inputOption)
		{
			case 0:
				return e_back;
			case 1:
				printf("\nEnter the name you want to search: ");
				scanf("%s", name);

				for (int index = 0; index < size; index++)
				{
					info = searchByName(&info[index], addressBookSize, name);
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

			case 2:
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

			case 3:
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
			case 4:
				printf("Enter the Serial Number ID you want to search: ");
				scanf("%d", siNum);
				for (int index = 0; index < size; index++)
				{
					info = searchBySiNum(&info[index], addressBookSize, siNum);
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




		}
	} 
	while (inputOption != 0);

	return e_success;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	int option;

	do
	{
		contactMenu("Delete by...");

		option = get_option(NUM, "");

		switch (option)
		{
		case e_first_opt:
			break;
		case e_second_opt:
			break;
		case e_third_opt:
			break;
		case e_fourth_opt:
			break;
		case e_fifth_opt:
			printf("Now exiting delete_contact...");
			return e_success;
		}

	} while (option != e_fifth_opt);

	return e_success;
}
