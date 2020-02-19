#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "classfile_structs.h"
#include "classfile_consts.h"
#include "printclass.h"
#include "loader.h"

int main(int argc, const char* argv[])
{
	if (argc < 2)
	{
		printf("Not enough parameters, did you specify the .class file?\n");
		return 1;
	}
	printf("%s\n", argv[1]);
	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("Error opening file.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *data = malloc(size);
	size_t read = fread(data, 1, size, fp);
	if (read != size)
	{
		printf("Didn't read all of file. ");
	}
	printf("Read %li bytes from .class file.\n\n", size);
	fclose(fp);
	
	class_file class;
	decode_class_header((unsigned char *)data, size, &class);
	print_class_header(&class);

	return 0;
}


