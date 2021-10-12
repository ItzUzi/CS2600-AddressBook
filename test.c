#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"


void main()
{
    AddressBook *tBook = malloc(sizeof(AddressBook));
    
    //testing assinging stuff to tBook
    tBook->count = 2;
    printf("%i\n", tBook->count);

    //test contacts
    ContactInfo c1;
    ContactInfo c2;
    ContactInfo cArray[] = {c1, c2};


    //testing assignments to c1Name and printing[WORKS]
    char *c1Name = tBook->list[0].name[0];
    strcpy(c1Name, "Ruby");
    char *c1Phone = tBook->list[0].phone_numbers[0];
    strcpy(c1Phone, "8180658901");
    char *c1Phoneb = tBook->list[0].phone_numbers[1];
    strcpy(c1Phoneb, "8186589123");
    tBook->list[0].si_no = 21;

    char *c2Name = tBook->list[1].name[0];
    strcpy(c2Name, "Marvin");



    printf("%s\n", c1Name);
    printf("%s\n", tBook->list[0].phone_numbers[1]);
    //printf("%s\n", tBook->list[0].name+sizeof(char));

    //Print out size of an array (WORKS);
    printf("Size: %i\n", sizeof(tBook->list[0].phone_numbers)/NUMBER_LEN);
    


    printf("\n");


    //Actual function
    for (int i=0; i<tBook->count;i++)
    {
        printf("Name: ");
        printf("%s", tBook->list[i].name);

        printf("\nPhone Numbers: \n");
        for(int j=0; j<PHONE_NUMBER_COUNT; j++)
        {
            if (strcmp(tBook->list[i].phone_numbers[j], "\0")==0 || (int)*tBook->list[i].phone_numbers[j]>=57 && (int)*tBook->list[i].phone_numbers[j]<= 48)
            {
                continue;
            }else{
                printf("\t%s\n", tBook->list[i].phone_numbers[j]);
            }
        }

        printf("\nEmail Addresses: \n");
        for(int k=0; k<EMAIL_ID_COUNT; k++)
        {
            if (strcmp(tBook->list[i].email_addresses[k], "\0")==0)
            {
                continue;
            }else{
                printf("\t%s\n", tBook->list[i].email_addresses[k]);
            }
        }

        printf("\nsi_no: %i\n\n", tBook->list[i].si_no);

    }
}