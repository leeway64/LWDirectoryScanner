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
        case 3: {  // Print out the directory in a tree-like format
            char *secondArgument = argv[1];
            char *directory = argv[2];
            if (!strcmp(secondArgument, treeCommand)) {
                printDirectoryDriver(directory);
            } else {
                printf("Incorrect command! Run with --help for more information.\n");
            }
            break;
        }

        case 2: {  // Either summarize and serialize the directory or print the help message
            const char *secondArgument = argv[1];

            tinydir_dir dir;
            signed int open_dir = tinydir_open(&dir, secondArgument);
            if (!strcmp(secondArgument, helpCommand)) {
                printHelp();
            } else if (open_dir != -1) {
                // "scanDirectoryPointer" is a function pointer. I can use function pointers to
                // pass functions as parameters to other functions.
                dirSummary (*scanDirectoryPointer)(const char* dirName) = scanDirectory;
                dirSummary summary = scanDirectoryPointer(secondArgument);

                printf("Directory selected: %s\n", secondArgument);
                printf("\tNumber of directories: %i\n", summary.counts.directories);
                printf("\tNumber of files: %i\n", summary.counts.files);
                printf("\tDeepest folder depth: %i\n\n", summary.deepestDepth);

                tinydir_file file;
                tinydir_file_open(&file, secondArgument);
                strcat(file.name, "_summary.cbor");
                serializeSummary(summary, file.name);
            } else {
                printf("That directory does not exist\n");
            }

            tinydir_close(&dir);
            break;
        }
        default:
            printf("Too few arguments! Run with --help for more information.\n");
    }
    cvector_free(depthsVector);

    return 0;
}
