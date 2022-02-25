#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbor.h"

#include "scanner_helpers.h"


int main(int argc, char** argv)
{
	// Preallocate the map structure
	cbor_item_t * root = cbor_new_definite_map(2);

	if (argc == 3)
	{
		char* secondArgument = argv[1];
		char* treeCommand = "--tree";
		if (!strcmp(secondArgument, treeCommand))
		{
			printf("tree activated: %s\n", argv[1]);
			//printDirectory();
		}
		else
		{
			printf("Incorrect command! Run with --help for more information.\n");			
		}
	}
	
	if (argc == 2)
	{
		char* secondArgument = argv[1];
		char* helpCommand = "--help";
		
		if (!strcmp(secondArgument, helpCommand))
		{
			printHelp();
		}
		else if (0 /*check if the second argument is a directory that exists*/)
		{
			
		}
		else
		{
			printf("Incorrect command! Run with --help for more information.\n");			
		}		
	}
	
	if (argc == 1)
	{
		printf("Incorrect command! Run with --help for more information.\n");					
	}
	
    printf("This program has %d arguments: \n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
	}
	return 0;
}
