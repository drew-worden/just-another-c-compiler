#include <stdio.h>
#include <stdbool.h>

#ifndef COMPILER_H
#define COMPILER_H

struct position
{
	int line;
	int column;
	const char *filename;
};

enum
{
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_SYMBOL,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_COMMENT,
	TOKEN_TYPE_NEWLINE
};

struct token
{
	int type;
	int flags;
	union
	{
		char char_val;
		const char *string_value;
		unsigned int integer_number;
		unsigned long long_number;
		unsigned long long long_long_number;
		void *any;
	};
	bool whitespace;
	const char *between_brackets;
};

struct lex_process;
typedef char (*LEXER_PROCESS_NEXT_CHAR)(struct lexer_process *process);
typedef char (*LEXER_PROCESS_PEEK_CHAR)(struct lexer_process *process);
typedef void (*LEXER_PROCESS_PUSH_CHAR)(struct lexer_process *process, char c);

struct lexer_process_functions
{
	LEXER_PROCESS_NEXT_CHAR next_char;
	LEXER_PROCESS_PEEK_CHAR peek_char;
	LEXER_PROCESS_PUSH_CHAR push_char;
};

struct lexer_process
{
	struct position position;
	struct vector *token_vector;
	struct compiler_process *compiler_process;
	int current_expression_count;
	struct buffer *parentheses_buffer;
	struct lexer_process_functions *function;
	void *private;
};

enum
{
	COMPILER_FILE_COMPILED_OK,
	COMPILER_FAILED_WITH_ERRORS
};

struct compiler_process
{
	int flags;
	struct position position;
	struct compiler_process_input_file
	{
		FILE *file;
		const char *absolute_path;
	} compiler_file;

	FILE *output_file;
};

int compile_file(const char *input_filename, const char *output_filename, int flags);
struct compiler_process *create_compiler_process(const char *input_filename, const char *output_filename, int flags);

#endif