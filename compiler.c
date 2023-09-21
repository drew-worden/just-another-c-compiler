#include "compiler.h"

int compile_file(const char* input_filename, const char* output_filename, int flags)
{
	struct compiler_process* process = create_compiler_process(input_filename, output_filename, flags);
	if (!process) {
		return COMPILER_FAILED_WITH_ERRORS;
	}

	//Pass through lexer

	//Pass through parsing

	//Pass through code generation

	return COMPILER_FILE_COMPILED_OK;
}