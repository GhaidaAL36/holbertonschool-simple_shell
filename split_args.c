#include "main.h"

/**
	* split_args - Splits the input command into arguments.
	*/
void split_args(char *command, char **args)
{
	char *token;
	int i = 0;

	token = strtok(command, " ");
	while (token != NULL && i < 199)
	{
	args[i++] = token;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
