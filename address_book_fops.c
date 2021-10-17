#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"


Status load_file(AddressBook *address_book)
{	
	ContactInfo *ptr = (ContactInfo*) malloc((ptr, 1 * sizeof(ContactInfo)));
	address_book->count = 0;
	
	FILE *fp = address_book->fp;
	int ret;
	int count = 0, index = 0;
	char buffer[500];
	char temp[500];
	char check;

	ret = access(DEFAULT_FILE, F_OK); 

	if (ret == 0)
	{
		fp = fopen(DEFAULT_FILE, "r");

		while(fgets(buffer, 500, fp) && check != EOF){
			count++;
			strcpy(temp, buffer);
			address_book->list = ptr;

			int si_num;
			char check[500];
			strcpy(check, strtok(temp, ","));
			strcpy(address_book->list[index].name[0], check);

			for(int i = 0; i < 11; i++){
				strcpy(check,strtok(NULL, ","));
				if(i >= 0 && i < 5)
					strcpy(address_book->list[index].phone_numbers[i], check);
				else if(i >= 5 && i < 10)
					strcpy(address_book->list[index].email_addresses[i-5], check);
				else{
					si_num = strtol(check, NULL, 10);
					address_book->list[index].si_no = si_num;
				}
			}
			ptr = (ContactInfo*) realloc(ptr, ((count+sizeof(int)) * sizeof(ContactInfo)));
			index++;
		}

	}
	else
		fp = fopen(DEFAULT_FILE, "w");

	fclose(fp);

	address_book->count = count;
	free(address_book->list);

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	char buffer[32];
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	while(fgets(buffer, 40, address_book->fp))
	{
		fprintf(address_book->fp,"hello%s,%s,%s\n", address_book->list->name, address_book->list->phone_numbers, address_book->list->email_addresses);
	}

	if (address_book->fp == NULL)
	{
		printf("Saving failed");
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
