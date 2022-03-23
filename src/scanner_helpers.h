#ifndef LWDIRECTORYSCANNER_SCANNER_HELPERS_H
#define LWDIRECTORYSCANNER_SCANNER_HELPERS_H

#include <tinydir.h>

void printDirectoryDriver(const char* dirName);

void printDirectory(tinydir_dir dir, unsigned int level);

struct dirSummary scanDirectory(tinydir_dir dir);

// "static" keyword indicates that this function can only be used in it own object file.
static unsigned int countDirDepth();

static unsigned int countNumberOfFiles();

static unsigned int countNumberOfDirs();

void serialize(struct dirSummary summary);

void printHelp();

#endif //LWDIRECTORYSCANNER_SCANNER_HELPERS_H
