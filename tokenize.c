#include "main.h"

/**
 * tokenize - Split user input into arguments
 * @input: User input string
 * @args: Argument vector
 *
 * Return: Nothing
 */
void tokenize(char *input, char *args[])
{
	char *token, *temp;
	unsigned int i = 0;

	token = strtok(input, " ");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		exit(0);

	/* env builtin */
	if (strcmp(args[0], "env") == 0 && args[1] == NULL)
	{
		printEnv();
		return;
	}

	/* exit builtin */
	if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
	{
		exit(0);
	}

	/* Handle PATH */
	temp = strdup(args[0]);
	args[0] = handle_path(args[0]);

	if (args[0] != NULL)
	{
		free(temp);
		exec(args, input);
		return;
	}

	fprintf(stderr, "./hsh: 1: %s: not found\n", temp);
	free(temp);
	exit(127);
}
