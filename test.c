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
    ContactInfo contArray[size];
    addBook.list = contArray;

    ContactInfo ptr;
    char name[32];

    strcpy(addBook.list[0].name[0], "Uzi");
    strcpy(addBook.list[0].phone_numbers[0], "3235561034");
    strcpy(addBook.list[0].phone_numbers[1], "3234480109");
    addBook.list[0].si_no = 323;
    printf("phone num is: %s", addBook.list[0].phone_numbers[0]);
    printf("%d", sizeof(addBook.list[0].name[0]));

    Status delete_contact(AddressBook *address_book);


    int result = delete_contact(&addBook);

    return 0;
}
