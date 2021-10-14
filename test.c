#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"


int main(int argc, char const *argv[])
{
    AddressBook addBook;

    int size = addBook.count;
    ContactInfo contArray[size + 1];
    addBook.list = contArray;

    ContactInfo ptr;
    char name[32];

    strcpy(addBook.list[0].name[0], "Uzi");
    strcpy(addBook.list[0].phone_numbers[0], "3235561034");
    strcpy(addBook.list[0].phone_numbers[1], "3234480109");
    addBook.list[0].si_no = 323;
    strcpy(addBook.list[1].name[0], "Iggy");
    Status menu(AddressBook *address_book);


    int result = menu(&addBook);

    return 0;
}
