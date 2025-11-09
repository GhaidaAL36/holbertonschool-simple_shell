#include "main.h"

/**
	* split_args - splits a command string into arguments
	* @command: the command string to split
	* @args: array to store the resulting arguments
	*/
void split_args(char *command, char **args)
{
	char *copy, *token;
	int i = 0;

	if (command == NULL)
	{
	args[0] = NULL;
	return;
	}

	while (*command == ' ' || *command == '\t' || *command == '\n')
	command++;

	if (*command == '\0')
	{
	args[0] = NULL;
	return;
	}

	copy = _strdup(command);
	if (!copy)
	{
	args[0] = NULL;
	return;
	}

	token = strtok(copy, " \t\n");
	while (token && i < 199)
	{
	args[i] = _strdup(token);
	i++;
	token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	free(copy);
}

