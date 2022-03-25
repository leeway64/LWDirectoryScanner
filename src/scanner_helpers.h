#ifndef LWDIRECTORYSCANNER_SCANNER_HELPERS_H
#define LWDIRECTORYSCANNER_SCANNER_HELPERS_H

#include <tinydir.h>

// This is a struct of structs
// "typedef" simplifies syntax for declaring variables
// "volatile" means that this dirSummary struct isn't optimized by the compiler.
// "volatile" is usually used in cases where the variable might be changed by an outside process.
typedef volatile struct dirSummary
{
    unsigned int deepestDepth;
    struct counts  // I declare a new struct here...
    {
        unsigned int files;
        unsigned int directories;
    } counts;  // But I'm initializing a new variable here.
} dirSummary;


void printDirectoryDriver(const char* dirName);

void printDirectory(tinydir_dir dir, unsigned int level);

dirSummary scanDirectory(const char* dirName);

// "static" keyword indicates that this function can only be used in it own object file.
static unsigned int countDirDepth(tinydir_dir dir);

static unsigned int countFiles(tinydir_dir dir);

static unsigned int countDirs(tinydir_dir dir);

void serializeSummary(const dirSummary summary);

void printHelp();

#endif //LWDIRECTORYSCANNER_SCANNER_HELPERS_H
