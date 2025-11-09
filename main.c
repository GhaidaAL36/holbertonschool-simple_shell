#include <stddef.h>
#include "main.h"
/**
	* main - Entry point of the simple shell.
	* @argc: Argument count.
	* @argv: Argument vector.
	*
	* Return: Always 0.
	*/
int main(int argc __attribute__((unused)), char *argv[])
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nread;
	char *trimmed_input;

	if (isatty(STDIN_FILENO))
	print_prompt();

	nread = read_input(&input, &len);

	while (nread != -1)
	{
	if (nread > 1)
	{
	trimmed_input = trim_whitespace(input);

	if (trimmed_input[0] != '\0')
	execute_command(trimmed_input, argv[0]);
	}

	if (isatty(STDIN_FILENO))
	print_prompt();

	nread = read_input(&input, &len);
	}

	free(input);
	return (0);
}
