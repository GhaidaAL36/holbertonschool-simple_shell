#include "main.h"

/**
 * split_args - splits a command string into arguments
 * @command: the command string to split
 * @args: array to store the resulting arguments
 *
 * This function tokenizes the command string using space as a delimiter
 * and fills the args array with the individual arguments. The last
 * element of args is set to NULL.
 *
 * Return: void
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
