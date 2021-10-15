#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{	FILE *fp = address_book->fp;
	int ret;
	int count, check;
	count = 0;
	char buffer[200];
	char tdarray[200][200];
	check = 0;

	ret = access(DEFAULT_FILE, F_OK); 

	if (ret == 0)
	{
		fp = fopen(DEFAULT_FILE, "r");
		
		printf("count is %d\n", count);

		while(fgets(buffer, 200, fp)){
			
			count++;
		}

		printf("count is %d\n", count);

		fclose(fp); 
	}
	else
	{
		fp = fopen(DEFAULT_FILE, "w");
		fclose(fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	fclose(address_book->fp);

	return e_success;
}
