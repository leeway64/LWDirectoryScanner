#include <stdio.h>
#include <string.h>

#include "scanner_helpers.h"

// "extern" means these variables are global. They can be accessed from any other translation unit
// (source file) in this program.
extern const char* treeCommand = "--tree";
extern const char* helpCommand = "--help";

int main(int argc, char** argv)
{
    switch(argc)
    {
        case 3: {
            char *secondArgument = argv[1];
            char *directory = argv[2];
            if (!strcmp(secondArgument, treeCommand)) {
                printDirectoryDriver(directory);
            } else {
                printf("Incorrect command! Run with --help for more information.\n");
            }
            break;
        }
        case 2: {
            char *secondArgument = argv[1];

            tinydir_dir dir;
            signed int open_dir = tinydir_open(&dir, secondArgument);
            if (!strcmp(secondArgument, helpCommand)) {
                printHelp();
            } else if (open_dir != -1) {
                // "scanDirectoryPointer" is a function pointer. I can use function pointers to
                // pass functions as parameters to other functions.
                dirSummary (*scanDirectoryPointer)(tinydir_dir dir) = scanDirectory;
                dirSummary summary = scanDirectoryPointer(dir);
                printf("Directory selected: %s\n", secondArgument);
                printf("\tDeepest folder depth: %i\n", summary.deepestDepth);
                printf("\tNumber of directories: %i\n", summary.counts.directories);
                printf("\tNumber of files: %i\n", summary.counts.files);
            } else {
                printf("That directory does not exist\n");
            }
            break;
        }
        default:
            printf("Too few arguments! Run with --help for more information.\n");
    }
	return 0;
}
