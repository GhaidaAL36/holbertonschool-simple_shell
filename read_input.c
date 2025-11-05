#include "simple_shell.h"

/**
 * read_input - reads a line from stdin
 * Return: pointer to the read line
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * parse_line - split input into arguments
 * @line: input string
 * Return: array of arguments
 */
char **parse_line(char *line)
{
	char **args = NULL;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}
