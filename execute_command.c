#include "main.h"

/**
	* execute_command - Executes a given command (with PATH handling).
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
