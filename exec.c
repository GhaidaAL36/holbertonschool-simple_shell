#include "main.h"

void execute_command(char **args)
{
	pid_t pid;
	char *path;
	struct stat st;

	if (!args || !args[0])
		return;

	if (stat(args[0], &st) == 0)
		path = args[0];
	else
		path = find_path(args[0]);

	if (!path)
	{
		write(STDERR_FILENO, "not found\n", 10);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
			perror("execve");
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);

	if (path != args[0])
		free(path);
}
