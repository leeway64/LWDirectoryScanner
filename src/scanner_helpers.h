#ifndef LWDIRECTORYSCANNER_SCANNER_HELPERS_H
#define LWDIRECTORYSCANNER_SCANNER_HELPERS_H

#include <tinydir.h>

void printDirectoryDriver(const char* dirName);

void printDirectory(tinydir_dir dir, int level);

void scanDirectory();

unsigned int countDirDepth();

unsigned int countNumberOfFiles();

unsigned int countNumberOfDirs();

void serialize();

void printHelp();

#endif //LWDIRECTORYSCANNER_SCANNER_HELPERS_H
