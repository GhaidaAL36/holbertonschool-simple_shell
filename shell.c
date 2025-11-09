#define _GNU_SOURCE
#include "main.h"

/**
 * spacesCheck - Check if a string contains only spaces
 * @str: String to check
 *
 * Return: 1 if only spaces, 0 otherwise
 */
int spacesCheck(const char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
	char *args[64] = {NULL};
	size_t input_size = 0;
	ssize_t input_read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		input_read = getline(&input, &input_size, stdin);

		if (input_read == EOF)
		{
			free(input);
			exit(0);
		}

		if (input_read > 0 && input[input_read - 1] == '\n')
			input[input_read - 1] = '\0';

		if (!spacesCheck(input))
			tokenize(input, args);
	}

	free(input);
	return (0);
}
