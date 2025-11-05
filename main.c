#include "simple_shell.h"

/**
 * main - Entry point of the simple shell program.
 * @argc: Argument count.
 * @argv: Argument vector (array of strings).
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

input = read_input();

	while (nread != -1)
	{
		if (input[nread - 1] == '\n')
			input[nread - 1] = '\0';

		trimmed_input = trim_whitespace(input);

/*  Handle exit built-in */
if (strcmp(trimmed_input, "exit") == 0)
{
    free(input);  /* مهم جداً عشان ما يصير memory leak */
    return 0;     /* خروج نظيف */
}

if (trimmed_input[0] != '\0')
    execute_command(trimmed_input, argv[0]);


		if (isatty(STDIN_FILENO))
			print_prompt();

		nread = read_input(&input, &len);
	}

	free(input);
	return (0);
}
