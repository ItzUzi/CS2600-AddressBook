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

static ContactInfo* searchAddressBook(ContactInfo *ptr, int bookSize, const void *targetPtr, int limit, int (*functionPtr)(const void *, ContactInfo*, int)){


    int counter = 0;
    do{
        if((*functionPtr)(targetPtr, ptr, counter) == 0)
            return (ContactInfo*) ptr;
        else
            counter++;
    }while(counter < limit);
     return NULL;

 }

static int compareSiNum(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return * (int *) targetPtr != tableValuePtr ->si_no;
}

ContactInfo* searchBySiNum(ContactInfo *ptr, int size, int siNum){
    return searchAddressBook(ptr, size, &siNum, 0, compareSiNum);
}