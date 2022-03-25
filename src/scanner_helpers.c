#include <stdio.h>
#include <cbor.h>

#include "scanner_helpers.h"

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

dirSummary scanDirectory(tinydir_dir dir)
{
    // "register" keyword tells compiler to store variable in CPU instead of in memory. This allows
    // for faster access.
    register dirSummary summary;
    summary.deepestDepth = countDirDepth(dir);
    summary.counts.files = countNumberOfFiles(dir);
    summary.counts.directories = countNumberOfDirs(dir);
    return summary;
}

static unsigned int countDirDepth(tinydir_dir dir)
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

static unsigned int countNumberOfFiles(tinydir_dir dir)
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

static unsigned int countNumberOfDirs(tinydir_dir dir)
{
    return 0;
}

void serializeSummary(const dirSummary summary)
{
	// Preallocate the map structure
	cbor_item_t * root = cbor_new_definite_map(3);

    //Add the directory summary
	cbor_map_add(root, (struct cbor_pair) {
		.key = cbor_move(cbor_build_string("deepest_depth")),
		.value = cbor_move(cbor_build_uint64(summary.deepestDepth))
	});

    cbor_map_add(root, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("directories")),
            .value = cbor_move(cbor_build_uint64(summary.counts.directories))
    });

    cbor_map_add(root, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("files")),
            .value = cbor_move(cbor_build_uint64(summary.counts.files))
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
	printf("    <DIRECTORY>           Scans <DIRECTORY> and serializes a summary of the directory statistics into a CBOR file.\n");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>.\n");
}
