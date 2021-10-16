#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

static ContactInfo* searchAddressBook(ContactInfo *ptr, int bookSize, const void *targetPtr,
                            int limit, int (*functionPtr)(const void *, ContactInfo*, int)){
    
    int counter = 0;
    do{
        if((*functionPtr)(targetPtr, ptr, counter) == 0)
            return (ContactInfo*) ptr;
        else
            counter++;
    }
    while(counter < limit);
    return NULL;

}

static int compareName(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return strcmp((char *) targetPtr, (char*)tableValuePtr->name[0]);
}

static int comparePhNum(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return strcmp((char *) targetPtr, (char *)tableValuePtr->phone_numbers[index]);
}

static int compareEmail(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return strcmp((char *) targetPtr, (char *) tableValuePtr->email_addresses[index]);
}

static int compareSiNum(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return * (int *) targetPtr != tableValuePtr ->si_no;
}

ContactInfo* searchByName(ContactInfo *ptr, int size, char *name){
    int limit = sizeof(ptr->name)/sizeof(ptr->name[0]);
    return searchAddressBook(ptr, size, name, limit, compareName);
}

ContactInfo* searchByPhNum(ContactInfo *ptr, int size, char *phoneNum){
    int limit = (sizeof(ptr->phone_numbers) / sizeof(ptr->phone_numbers[0]));
    return searchAddressBook(ptr, size, phoneNum, limit, comparePhNum);
}

ContactInfo* searchByEmail(ContactInfo *ptr, int size, char *emailAddress){
    int limit = (sizeof(ptr->email_addresses) / sizeof(ptr->email_addresses[0]));
    return searchAddressBook(ptr, size, emailAddress, limit, compareEmail);
}

ContactInfo* searchBySiNum(ContactInfo *ptr, int size, int siNum){
    return searchAddressBook(ptr, size, &siNum, 0, compareSiNum);
}