#include "main.h"

/**
	* handle_builtins - executes built-in commands if found
	* @args: tokenized command
	* @line: input line to free if exit
	* @envp: environment variables
	* @status: pointer to shell status
	*
	* Return: 1 if a built-in was executed, 0 otherwise
	*/
int handle_builtins(char *args[], char *line, char **envp, int *status)
{
	int i;

	if (!args[0])
	return (1);

	if (strcmp(args[0], "exit") == 0)
	{
	free(line);
	exit(*status);
	}

	if (strcmp(args[0], "env") == 0)
	{
	for (i = 0; envp[i]; i++)
	{
	write(STDOUT_FILENO, envp[i], strlen(envp[i]));
	write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
	}
	return (0);
}

