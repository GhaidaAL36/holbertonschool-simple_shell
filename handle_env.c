#include "main.h"

/**
	* handle_env - prints the current environment if command is "env"
	* @args: array of command arguments
	* @envp: array of environment variables
	*
	* Return: 1 if the command was "env", 0 otherwise
	*/
int handle_env(char *args[], char **envp)
{
	int j;

	if (strcmp(args[0], "env") == 0)
	{
	for (j = 0; envp[j]; j++)
	{
	write(STDOUT_FILENO, envp[j], strlen(envp[j]));
	write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
	}
	return (0);
}
