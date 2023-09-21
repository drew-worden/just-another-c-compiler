#include <stdio.h>
#include "compiler.h"

int main()
{
	int response = compile_file("./test.c", "./test", 0);
	if (response == COMPILER_FILE_COMPILED_OK)
	{
		printf("Everything compiled fine.\n");
	}
	else if (response == COMPILER_FAILED_WITH_ERRORS)
	{
		printf("Compilation failed.\n");
	}
	else
	{
		printf("Unknown response from file compilation\n");
	}
	return 0;
}