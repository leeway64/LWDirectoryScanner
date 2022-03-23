#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner_helpers.h"

int main(int argc, char** argv)
{
//    printDirectoryDriver("C:\\Users\\leewa\\Documents\\Important documents\\Computer Science\\C_Projects\\LWDirectoryScanner\\tests\\test_dirs");
//    serialize();
	/*
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

	    tinydir_dir dir;
        signed int open_dir = tinydir_open(&dir, secondArgument);
		if (!strcmp(secondArgument, helpCommand))
		{
			printHelp();
		}
		else if (open_dir != -1)
		{
			dirSummary summary = scanDirectory();
			printf("\tDeepest folder depth: %i\n", summary.deepestDepth);
			printf("\tNumber of directories: %i\n", summary.counts.directories);
			printf("\Number of files: %i\n", summary.counts.files);
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
    */
	return 0;
}
