#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cbor.h>
#include <tinydir.h>

#include "scanner_helpers.h"


int main(int argc, char** argv)
{
//    tinydir_file file;
//
//    if (tinydir_file_open(&file, "C:\\Users\\leewa\\Documents\\Important documents\\Computer Science\\C_Projects\\LWDirectoryScanner\\tests\\test_dirs\\a") == -1)
//    {
//        perror("Error opening file");
//        return 1;
//    }
//    printf("Path: %s\nName: %s\nExtension: %s\nIs dir? %s\nIs regular file? %s\n",
//           file.path, file.name, file.extension,
//           file.is_dir?"yes":"no", file.is_reg?"yes":"no");
    printDirectoryDriver("C:\\Users\\leewa\\Documents\\Important documents\\Computer Science\\C_Projects\\LWDirectoryScanner\\tests\\test_dirs");



    /*
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
	*/



	/*
	if (argc == 3)
	{
		char* secondArgument = argv[1];
		char* treeCommand = "--tree";
		if (!strcmp(secondArgument, treeCommand))
		{
			printf("tree activated: %s\n", argv[1]);
			//printDirectory();
		}
		else
		{
			printf("Incorrect command! Run with --help for more information.\n");			
		}
	}
	
	if (argc == 2)
	{
		char* secondArgument = argv[1];
		char* helpCommand = "--help";
		
		if (!strcmp(secondArgument, helpCommand))
		{
			printHelp();
		}
		else if (0 /*check if the second argument is a directory that exists)
		{
			
		}
		else
		{
			printf("Incorrect command! Run with --help for more information.\n");			
		}		
	}
	
	if (argc == 1)
	{
		printf("Incorrect command! Run with --help for more information.\n");					
	}
	
    printf("This program has %d arguments: \n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
	}*/
	return 0;
}
