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
    char *c2Name = tBook->list[0].name[1];
    strcpy(c2Name, "Marvin");

    printf("%s\n", c1Name);

    printf("%s\n", tBook->list[0].name);
    printf("%s", tBook->list[0].name+sizeof(char));
    

}