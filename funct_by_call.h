#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
#include "address_book_menu.h"
#include "address_book.h"

static ContactInfo* searchAddressBook(ContactInfo *ptr, int bookSize, const void *targetPtr,
                            int (*functionPtr)(const void *, ContactInfo*, int)){
    
    int counter = 0;
    printf("SearchAddressBook\n");
    ContactInfo *endPtr = ptr + bookSize;
    for(; ptr < endPtr; ptr++)
        printf("ptr: %s\n",ptr);

        if(counter < (sizeof(ptr->name)/sizeof(ptr->name[0])))
            counter ++;

        if((*functionPtr)(targetPtr, ptr, counter) == 0){
            return (ContactInfo*) ptr;
        }
    return NULL;

}

static int compareName(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    printf("CompareName\n");
    return strcmp((char *) targetPtr, (char *) tableValuePtr -> name[index]);
}

static int comparePhNum(const void *targetPtr, ContactInfo *tableValuePtr, int index){
    return strcmp((char *) targetPtr, (char *) tableValuePtr -> phone_numbers[index]);
}

ContactInfo* searchByName(ContactInfo *ptr, int size, char *name){
    printf("\nLooking for %s\n", name);
    return searchAddressBook(ptr, size, name, compareName);
}

ContactInfo* searchByPhNum(ContactInfo *ptr, int size, char *phoneNum){
    return searchAddressBook(ptr, size, phoneNum, comparePhNum);
}