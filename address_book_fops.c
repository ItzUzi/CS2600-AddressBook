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
	FILE *fp = address_book->fp;
	ContactInfo *ptr;
	int counter = 0;
	int count = address_book->count;
	fp = fopen(DEFAULT_FILE, "w");
	while(counter < count){
		ptr = address_book->list;
		fprintf(fp, "%s,", ptr[counter].name[0]);

		for(int i = 0; i < PHONE_NUMBER_COUNT; i++)
			fprintf(fp,"%s,", ptr[counter].phone_numbers[i]);
		for(int i = 0; i < EMAIL_ID_COUNT; i++)
			fprintf(fp, "%s,", ptr[counter].email_addresses[i]);

		fprintf(fp, "%d", ptr[counter].si_no);

		if(counter != count - 1)
			fprintf(fp, "\n");
		counter++;
	}

	fclose(fp);

	return e_success;
}
