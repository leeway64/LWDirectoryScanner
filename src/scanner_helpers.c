#include <stdio.h>
#include <cbor.h>

#include "scanner_helpers.h"
#define CVECTOR_LOGARITHMIC_GROWTH
#include "../c-vector/cvector.h"

cvector_vector_type(unsigned int) depthsVector;

void printDirectoryDriver(const char* dirName)
{
    tinydir_dir dir;
    int open_dir_success = tinydir_open(&dir, dirName) != -1;
    if (!open_dir_success)
    {
        printf("That directory does not exist\n");
    }
    else
    {
        printf("Directory selected: %s/\n", dirName);
        printDirectory(dir, 1);
    }
    tinydir_close(&dir);
}

static void printDirectory(tinydir_dir dir, unsigned int level)
{
    tinydir_dir original_dir = dir;
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
        {
            // Print indentation
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

            if (file.is_dir) {
                // Set the name of dir to the file path
                tinydir_open(&dir, file.path);
                printDirectory(dir, level + 1);
                // Set dir back to what it was before recursion
                dir = original_dir;
            }
        }
        tinydir_next(&dir);
    }
}

dirSummary scanDirectory(const char* dirName)
{
    // "register" keyword tells compiler to store variable in CPU instead of in memory. This allows
    // for faster access.
    register dirSummary summary;

    tinydir_dir tinydir1;
    tinydir_open(&tinydir1, dirName);

    tinydir_dir tinydir2;
    tinydir_open(&tinydir2, dirName);

    tinydir_dir tinydir3;
    tinydir_open(&tinydir3, dirName);


    unsigned int depth = countDirDepth(tinydir1);
    summary.deepestDepth = depth;
    tinydir_close(&tinydir1);

    unsigned int dirs = countDirs(tinydir2);
    summary.counts.directories = dirs;
    tinydir_close(&tinydir2);

    unsigned int files = countFiles(tinydir3);
    summary.counts.files = files;
    tinydir_close(&tinydir3);

    return summary;
}

void exploreDirDepths(tinydir_dir dir, unsigned int currentDepth)
{
    tinydir_dir original_dir = dir;
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
        {
            if (file.is_dir) {
                // Set the name of dir to the file path
                cvector_push_back(depthsVector, currentDepth);
                tinydir_open(&dir, file.path);
                exploreDirDepths(dir, currentDepth + 1);
                // Set dir back to what it was before recursion
                dir = original_dir;
            }
        }
        tinydir_next(&dir);
    }
}

unsigned int vectorMax(cvector_vector_type(unsigned int)vector)
{
    unsigned int* iter;
    unsigned int maximum = 0;
    for (iter = cvector_begin(vector); iter != cvector_end(vector); ++iter)
    {
        if (*iter > maximum)
        {
            maximum = *iter;
        }
    }
    return maximum;
}

unsigned int countDirDepth(tinydir_dir dir)
{
    depthsVector = NULL;
    unsigned int currentDepth = 1;
    exploreDirDepths(dir, currentDepth);
    unsigned int maximum = vectorMax(depthsVector);

    cvector_free(depthsVector);
    return maximum;
}

unsigned int countFiles(tinydir_dir dir)
{
    unsigned int files = 0;
    tinydir_dir original_dir = dir;
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
        {

            if (file.is_dir) {
                // Set the name of dir to the file path
                tinydir_open(&dir, file.path);
                files += countFiles(dir);
                // Set dir back to what it was before recursion
                dir = original_dir;
            }
            else
            {
                ++files;
            }
        }
        tinydir_next(&dir);
    }
    dir = original_dir;
    return files;
}

unsigned int countDirs(tinydir_dir dir)
{
    unsigned int directories = 0;
    tinydir_dir original_dir = dir;
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
        {
            if (file.is_dir) {
                directories++;
                // Set the name of dir to the file path
                tinydir_open(&dir, file.path);
                directories += countDirs(dir);
                // Set dir back to what it was before recursion
                dir = original_dir;
            }
        }
        tinydir_next(&dir);
    }
    dir = original_dir;
    return directories;
}

void serializeSummary(const dirSummary summary, const char* outputFile)
{
    // Turn the summary struct's values into strings. This is because, for example, if I try to
    // write the integer 10 to a file, it gets treated as a new line character.
    unsigned int deepestDepth = summary.deepestDepth;
    unsigned int directories = summary.counts.directories;
    unsigned int files = summary.counts.files;

    char depthString[33];
    char directoriesString[33];
    char filesString[33];

    sprintf(depthString, "%i", deepestDepth);
    sprintf(directoriesString, "%i", directories);
    sprintf(filesString, "%i", files);


    // Preallocate the map structure
	cbor_item_t * root = cbor_new_definite_map(3);

    //Add the directory summary
	cbor_map_add(root, (struct cbor_pair) {
		.key = cbor_move(cbor_build_string("deepest_depth")),
		.value = cbor_move(cbor_build_string(depthString))
	});

    cbor_map_add(root, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("directories")),
            .value = cbor_move(cbor_build_string(directoriesString))
    });

    cbor_map_add(root, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("files")),
            .value = cbor_move(cbor_build_string(filesString))
    });

    // Output: `length` bytes of data in the `buffer`
    // Write the map to a .cbor file
	unsigned char * buffer;
	size_t buffer_size,
		length = cbor_serialize_alloc(root, &buffer, &buffer_size);

    FILE * writeFile = fopen(outputFile, "w");

    fwrite(buffer, 1, length, writeFile);
	free(buffer);

	fflush(writeFile);
	cbor_decref(&root);


    printf("Serialization complete: Directory summary has been serialized into %s\n", outputFile);
}

void printHelp()
{
    // Dynamically allocate memory
    char * first_line = malloc(64 * sizeof(char));
    strcpy(first_line, "Usage: LWDirectoryScanner [OPTIONS]");

	printf("%s\n", first_line);
	printf("Options:\n");
	printf("    <DIRECTORY>           Scans <DIRECTORY>, prints out a summary of the directory to the console, and "
           "serializes the summary into a CBOR file.\n");
	printf("    --tree <DIRECTORY>    Prints out the contents of <DIRECTORY> in a tree-like structure.\n");

    // Release the memory held by the first_line pointer. I can only use free on memory that has
    // been allocated with malloc.
    free(first_line);
}
