#include <stdio.h>
#include <tinydir.h>
#include "scanner_helpers.h"

void printDirectoryDriver(char* dirName)
{
    tinydir_dir dir;
    int open_dir_success = tinydir_open(&dir, dirName) != -1;
    if (!open_dir_success)
    {
        printf("That file or directory does not exist");
    }
    else
    {
        printf("Directory selected: %s/\n", dirName);
        printDirectory(dir, 1);
    }
}

void printDirectory(tinydir_dir dir, int level)
{
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
        {
            for (int i = 0; i < level; ++i)
            {
                printf("    ");
            }
            printf("%s", file.name);
            if (file.is_dir)
            {
                printf("/");
            }
            printf("\n");

//            if (file.is_dir) {
//                printDirectory(dir, level + 1);
//            }
        }
        tinydir_next(&dir);
    }
    tinydir_close(&dir);



//    if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
//    {
//        printf("%s", file.name);
//        if (file.is_dir)
//        {
//            printf("/");
//        }
//        printf("\n");
//    }
//
//    if (file.is_dir)
//    {
//        tinydir_readfile(&dir, &file);
//        for (1; 1; 1)
//        {
//            printDirectory(, level + 1);
//        }
//    }
}

void printHelp()
{
	printf("Usage: LWDirectoryScanner [OPTIONS]\n");
	printf("Options:\n");
	printf("    <DIRECTORY>           Scans <DIRECTORY> and serializes a summary of the directory statistics into a CBOR file.");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>.");
}
