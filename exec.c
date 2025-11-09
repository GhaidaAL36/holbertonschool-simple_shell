#include "main.h"

/**
 * _err - Handle command errors
 * @args: Argument vector
 *
 * Return: Nothing
 */
void _err(char *args[])
{
	fprintf(stderr, "%s: command not found\n", args[0]);
	perror("");
	free(args[0]);
	exit(98);
}

/**
 * exec - Execute command from input
 * @args: Argument vector
 * @input: Raw user input
 *
 * Return: Nothing
 */
void exec(char **args, char *input)
{
	int status;
	pid_t child_pid;

	if (access(args[0], X_OK) != 0)
		_err(args);

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(input);
		free(args[0]);
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		execve(args[0], args, environ);
		perror(args[0]);
		free(args[0]);
		exit(EXIT_FAILURE);
	}

	wait(&status);

	free(args[0]);
	free(input);
}
