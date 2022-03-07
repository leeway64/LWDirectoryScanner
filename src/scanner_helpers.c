#include <stdio.h>

#include "scanner_helpers.h"

void printDirectoryDriver(char* dirName)
{
	if (1)
	{
		printDirectory(dirName, 0);
	}
	else
	{
		printf(stderr, "That file or directory does not exist");
	}
}

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
	printf("    <DIRECTORY>           Scans <DIRECTORY> and serializes a summary of the directory statistics into a CBOR file.");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>.");
}
