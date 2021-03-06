#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"


int main(int argc, char const *argv[])
{
    AddressBook addBook;
    load_file(&addBook);
    int size = 100;
    ContactInfo contArray[3];
    addBook.list = contArray;
    addBook.count = 3;
    ContactInfo ptr;
    char name[32];


    for(int j = 0; j < 3; j++)
        for(int i = 0; i < PHONE_NUMBER_COUNT; i++){
            strcpy(addBook.list[j].phone_numbers[i], "");
            strcpy(addBook.list[j].email_addresses[i], "");
        }

    strcpy(addBook.list[0].name[0], "Uzi");
    strcpy(addBook.list[0].phone_numbers[0], "3235561034");
    strcpy(addBook.list[0].phone_numbers[1], "1312331231");
    strcpy(addBook.list[0].email_addresses[0], "ugaeta@cpp.edu");
    addBook.list[0].si_no = 323;
    strcpy(addBook.list[1].name[0], "Iggy");
    strcpy(addBook.list[1].phone_numbers[0], "3235561034");
    strcpy(addBook.list[1].email_addresses[0], "iggy@gmail.com");
    strcpy(addBook.list[2].name[0], "Uzi");
    strcpy(addBook.list[2].email_addresses[0], "ugaeta@cpp.edu");
    Status menu(AddressBook *address_book);


    int result = menu(&addBook);

    return 0;
}
