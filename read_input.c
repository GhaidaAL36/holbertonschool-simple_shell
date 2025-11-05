#include "simple_shell.h"
#include <stddef.h> /* for NULL */
#include <stdlib.h> /* for malloc, realloc */
#include <string.h> /* for strtok */

/**
 * read_line - reads a line from stdin using read()
 * Return: pointer to the line
 */
char *read_line(void)
{
	char *buffer;
	ssize_t bytes_read;
	size_t bufsize = 1024, i = 0;
	char c;

	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (NULL);

	while (1)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0 || c == '\n')
		{
			buffer[i] = '\0';
			return (buffer);
		}
		buffer[i++] = c;
		if (i >= bufsize)
		{
			bufsize += 1024;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return (NULL);
		}
	}
}

/**
 * split_line - split input string into tokens
 * @line: input string
 * Return: array of arguments
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = token;
		if (i >= bufsize - 1)
		{
			bufsize *= 2;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
