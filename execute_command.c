#include "main.h"

/**
	* execute_command - executes an external command
	* @args: tokenized command
	* @envp: environment variables
	*
	* Return: exit status of the command
	*/
int execute_command(char *args[], char **envp)
{
	pid_t pid;
	int status;
	char *path_cmd;

	path_cmd = find_command(args[0], envp);
	if (!path_cmd)
	{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, args[0], strlen(args[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	return (127);
	}

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	free(path_cmd);
	return (1);
	}
	else if (pid == 0)
	{
	execve(path_cmd, args, envp);
	perror("execve");
	_exit(EXIT_FAILURE);
	}
	else
	{
	wait(&status);
	free(path_cmd);
	if (WIFEXITED(status))
	return (WEXITSTATUS(status));
	return (1);
	}
}

