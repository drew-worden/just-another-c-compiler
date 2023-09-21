#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

struct compiler_process *create_compiler_process(const char *input_filename, const char *output_filename, int flags)
{
	FILE *input_file = fopen(input_filename, "r");
	if (!input_file)
	{
		return NULL;
	}

	FILE *output_file = NULL;
	if (output_filename)
	{
		FILE *output_file = fopen(output_filename, "w");
		if (!output_file)
		{
			return NULL;
		}
	}

	struct compiler_process *process = calloc(1, sizeof(struct compiler_process));
	process->flags = flags;
	process->compiler_file.file = input_file;
	process->output_file = output_file;

	return process;
}

char compiler_process_next_char(struct lexer_process *lexer_process)
{
	struct compiler_process *compiler_process = lexer_process->compiler_process;
	compiler_process->position.column += 1;
	char character = getc(compiler_process->compiler_file.file);
	if (character == "\n")
	{
		compiler_process->position.line += 1;
		compiler_process->position.column = 0;
	}

	return character;
}

char compiler_process_peek_char(struct lexer_process *lexer_process)
{
	struct compiler_process *compiler_process = lexer_process->compiler_process;
	char character = getc(compiler_process->compiler_file.file);
	ungetc(character, compiler_process->compiler_file.file);
	return character;
}

void compiler_process_push_char(struct lexer_process *lexer_process, char character)
{
	struct compiler_process *compiler_process = lexer_process->compiler_process;
	ungetc(character, compiler_process->compiler_file.file);
}