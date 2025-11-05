#include "main.h"

/**
 * execute - create child and run command
 * @argv: arguments array
 */
void execute(char **argv)
{
	pid_t pid;
	char *path;

	if (!argv || !argv[0])
		return;

	/* built-in env */
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		return;
	}

	path = argv[0];
	if (path[0] != '/' && path[0] != '.')
	{
		char *resolved = find_in_path(argv[0]);
		if (resolved)
			path = resolved;
		else
		{
			write(STDERR_FILENO, "not found\n", 10);
			return;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
			perror("execve");
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);

	if (path != argv[0])
		free(path);
}
