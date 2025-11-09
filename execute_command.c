#include "main.h"

/**
 * execute_command - executes a command
 * @command: command string to execute
 * @program_name: name of the shell program
 *
 * This function splits the command into arguments, resolves the full
 * path, forks a child process, and executes the command using execve.
 * The parent process waits for the child to finish.
 *
 * Return: void
 */
void execute_command(char *command, char *program_name)
{
	char *args[200];
	pid_t pid;

	split_args(command, args);
	if (args[0] == NULL)
	return;

	if (!resolve_path(args, program_name))
	return;

	pid = fork();
	if (pid == -1)
	{
	perror("fork failed");
	exit(1);
	}

	if (pid == 0)
	{
	if (execve(args[0], args, environ) == -1)
	{
	perror(program_name);
	exit(1);
	}
	}
	else
	wait(NULL);
}
