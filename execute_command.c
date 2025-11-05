#include "simple_shell.h"

void execute_command(char **args)
{
	char *cmd = args[0];
	char *path = getenv("PATH");
	char *token;
	char full[1024];
	struct stat st;

	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0)
			execve(cmd, args, environ);
		write(STDERR_FILENO, "./hsh: not found\n", 17);
		exit(127);
	}

	if (!path || *path == '\0')
	{
		write(STDERR_FILENO, "./hsh: not found\n", 17);
		exit(127);
	}

	token = strtok(path, ":");
	while (token)
	{
		strcpy(full, token);
		strcat(full, "/");
		strcat(full, cmd);
		if (stat(full, &st) == 0)
			execve(full, args, environ);
		token = strtok(NULL, ":");
	}
	write(STDERR_FILENO, "./hsh: not found\n", 17);
	exit(127);
}
