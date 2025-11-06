#include "main.h"

/**
 * tokenize - splits a string into tokens and executes
 * @input: user input
 * @args: argument array
 */
void tokenize(char *input, char *args[])
{
	char *token;
	unsigned int i = 0;

	token = strtok(input, " \t");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return;

	if (strcmp(args[0], "env") == 0)
	{
		printEnv();
		return;
	}
	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
	{
		free(input);
		exit(0);
	}

	args[0] = handle_path(args[0]);
	if (args[0] != NULL)
	{
		exec(args, input);
		free(args[0]);
	}
	else
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
}
