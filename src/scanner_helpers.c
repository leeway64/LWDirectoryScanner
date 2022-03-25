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

    //    serializeSummary(summary);
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

static unsigned int countFiles(tinydir_dir dir)
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

static unsigned int countDirs(tinydir_dir dir)
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
	printf("    <DIRECTORY>           Scans <DIRECTORY>, prints out a summary to the console, and "
           "serializes the summary of the directory statistics into a CBOR file.\n");
	printf("    --tree <DIRECTORY>    Print out the contents of <DIRECTORY>.\n");
}
