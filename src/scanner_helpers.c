#include <stdio.h>

#include "scanner_helpers.h"


void printDirectory(char* dirName, int level)
{
	for (int i = 0; i < level; ++i)
	{
		printf("    ");
	}
	printf("tree\n");
}

void printHelp()
{
	printf("Usage: LWDirectoryScanner [OPTIONS]\n");
	printf("Options:\n");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>");
}
