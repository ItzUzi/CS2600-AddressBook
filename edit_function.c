#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

extern Status save_file(AddressBook *address_book);

int edit_contact(AddressBook *address_book)
{
	/*
    //open file in read mode
	FILE *tfp, *sfp;
    tfp = fopen(address_book->fp, "r+");
    sfp=fopen("temp.txt","w");

	if(tfp = NULL)
    {
    	FILE_ERROR(DEFAULT_FILE);    //if can't open file
        exit(0);
    }
    */

    char nameE[NAME_LEN];
	char phoneE[NUMBER_LEN];
	char emailE[EMAIL_ID_LEN];
	int snE;
    int exit = -1;

    search_contact(address_book);
    printf("\nPress: [s] = Select, [q] | Cancel: ");
    char select;
    scanf("%c", &select);

    // review user input for next step
    if ( select == 'q' )
        return e_back;
    else if ( select != 's' )
        return e_no_match;

    printf("Select a Serial Number (S.No) to Edit: ");
    sacnf("%d", &snE);

    /*
    while(fscanf(tfp,"%s", address_book->list->si_no)!=EOF)
    {
        if(strcmp(snE,address_book->list->si_no)==0)
        {
            int *p = (int *) address_book->list->si_no;
        }
    }
    */

    do{
        menu_header("Edit Contact:");
	    printf("\n");
        printf("0. Back\n");
	    printf("1. Name       : %s\n",address_book->list->name);
	    printf("2. Phone No %d : %s\n", 1, address_book->list->phone_numbers[0]);
        int i = 1;
        while (address_book->list->phone_numbers[i] != NULL && i < PHONE_NUMBER_COUNT){
	        printf("            %d : %s\n", (i+1), address_book->list->phone_numbers[i]);
            i++;
        }
	    printf("3. Email ID %d : %s\n", 1, address_book->list->email_addresses[0]);
        while (address_book->list->email_addresses[i] != NULL && i < EMAIL_ID_COUNT){
	        printf("            %d : %s\n", (i+1), address_book->list->email_addresses[i]);
            i++;
        }
	    printf("\n");
	    printf("Please select an option: "); 
        int option;
        option = get_option(NUM, "");

        int n = 0;
        switch (option){
            case e_first_opt:
                exit = 0;
            case e_second_opt:
                printf("Enter Name: [Just enter removes the entry]: ");
                scanf("%s", nameE);
                // reset name
            case e_third_opt:
                while (!(n<=5 || n>=1)){
                    printf("Enter Phone Number index to be change [Max 5]: ");
                    scanf("%d", &n);
                }
                printf("Enter Phone Number %d: [Just enter removes the entry]: ", n);
                sanf("%s", phoneE[n]);
                // reset phone n
            case e_fourth_opt:
                while (!(n<=5 || n>=1)){
                    printf("Enter Email Address index to be change [Max 5]: ");
                    scanf("%d", &n);
                }
                printf("Enter Email Address %d: [Just enter removes the entry]: ", n);
                sanf("%s", emailE[n]);
                // reset email n
        }

    } (exit != 0);

	return e_success;
}