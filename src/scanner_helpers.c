#include <stdio.h>
#include <cbor.h>

#include "scanner_helpers.h"

// This is a struct of structs
// typedef simplifies syntax for declaring variables
typedef struct dirSummary
{
    unsigned int deepestDepth;
    struct counts  // I declare a new struct here...
    {
        unsigned int files;
        unsigned int directories;
    } counts;  // But I'm initializing a new variable here.

} dirSummary;

void printDirectoryDriver(const char* dirName)
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
    tinydir_close(&dir);
}

void printDirectory(tinydir_dir dir, unsigned int level)
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

struct dirSummary scanDirectory(tinydir_dir dir)
{
    // "register" keyword tells compiler to store variable in CPU instead of in memory. This allows
    // for faster access.
    register dirSummary summary;
    summary.deepestDepth = countDirDepth();
    summary.counts.files = countNumberOfFiles();
    summary.counts.directories = countNumberOfDirs();
    return summary;
}

static unsigned int countDirDepth()
{
//    tinydir_dir original_dir = dir;
//    while (dir.has_next)
//    {
//        tinydir_file file;
//        tinydir_readfile(&dir, &file);
//        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0)
//        {
//            // Print indentation
//            for (int i = 0; i < level; ++i)
//            {
//                printf("    ");
//            }
//
//            printf("%s", file.name);
//            if (file.is_dir)
//            {
//                printf("/");
//            }
//            printf("\n");
//
//            if (file.is_dir) {
//                // Set the name of dir to the file path
//                tinydir_open(&dir, file.path);
//                printDirectory(dir, level + 1);
//                // Set dir back to what it was before recursion
//                dir = original_dir;
//            }
//        }
//        tinydir_next(&dir);
//    }
    return 0;
}

static unsigned int countNumberOfFiles()
{
    return 0;
}

static unsigned int countNumberOfDirs()
{
    return 0;
}

void serialize(dirSummary summary)
{
	// Preallocate the map structure
	cbor_item_t * root = cbor_new_definite_map(2);
	//Add the content
	cbor_map_add(root, (struct cbor_pair) {
		.key = cbor_move(cbor_build_string("Is CBOR awesome?")),
		.value = cbor_move(cbor_build_bool(true))
	});
	cbor_map_add(root, (struct cbor_pair) {
		.key = cbor_move(cbor_build_uint8(42)),
		.value = cbor_move(cbor_build_string("Is the answer"))
	});
	//Output: `length` bytes of data in the `buffer`
	unsigned char * buffer;
	size_t buffer_size,
		length = cbor_serialize_alloc(root, &buffer, &buffer_size);

	fwrite(buffer, 1, length, stdout);
	free(buffer);

	fflush(stdout);
	cbor_decref(&root);
}

void printHelp()
{
	printf("Usage: LWDirectoryScanner [OPTIONS]\n");
	printf("Options:\n");
	printf("    <DIRECTORY>           Scans <DIRECTORY> and serializes a summary of the directory statistics into a CBOR file.");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>.");
}
