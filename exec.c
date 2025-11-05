#include "main.h"

void execute(char **argv)
{
	pid_t pid;
	char *cmd_path;

	if (!argv || !argv[0])
		return;

	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		return;
	}

	cmd_path = handle_path(argv[0]);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "not found\n", 10);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ) == -1)
			perror("execve");
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);

	if (strcmp(cmd_path, argv[0]) != 0)
		free(cmd_path);
}
