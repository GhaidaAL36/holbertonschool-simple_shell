#include "main.h"

/**
 * handle_builtins - Handle builtin commands
 * @args: Argument vector
 *
 * Return: 1 if handled, 0 otherwise
 */
int handle_builtins(char **args)
{
	if (strcmp(args[0], "env") == 0 && args[1] == NULL)
	{
		printEnv();
		return (1);
	}

	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
	{
		exit(0);
	}

	return (0);
}

/**
 * tokenize - Split input into arguments
 * @input: Raw input string
 * @args: Output argument array
 *
 * Return: Nothing
 */
void tokenize(char *input, char *args[])
{
	char *token, *tmp;
	unsigned int i = 0;

	token = strtok(input, " ");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (handle_builtins(args))
		return;

	tmp = strdup(args[0]);
	args[0] = handle_path(tmp);

	if (args[0])
	{
		exec(args, input);
		free(tmp);
		return;
	}

	fprintf(stderr, "./hsh: 1: %s: not found\n", tmp);
	free(tmp);
	exit(127);
}
