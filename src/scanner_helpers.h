#ifndef LWDIRECTORYSCANNER_SCANNER_HELPERS_H
#define LWDIRECTORYSCANNER_SCANNER_HELPERS_H

#include <tinydir.h>
#include "../c-vector/cvector.h"

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

extern cvector_vector_type(unsigned int) depthsVector;

/// Print the directory in a tree-like format.
/// @param dirName is the name of the directory to print.
void printDirectoryDriver(const char* dirName);

// "static" keyword indicates that this function can only be used in its own object file.
static void printDirectory(tinydir_dir dir, unsigned int level);

/// Analyze a directory, finding the number of files and directories in it, along with the deepest
/// directory depth.
/// @param dirName is the name of the directory to scan.
dirSummary scanDirectory(const char* dirName);

unsigned int countDirDepth(tinydir_dir dir);

unsigned int countFiles(tinydir_dir dir);

unsigned int countDirs(tinydir_dir dir);

unsigned int vectorMax(cvector_vector_type(unsigned int) vector);

/// Serialize the summary of the directory and write the summary to a CBOR file.
/// @param summary is the dirSummary struct that holds the summary.
/// @param outputFile is the name of the .cbor file to be created.
void serializeSummary(const dirSummary summary, const char* outputFile);

void printHelp();

#endif //LWDIRECTORYSCANNER_SCANNER_HELPERS_H
