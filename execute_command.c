#include "simple_shell.h"

/**
 * execute_command - Execute a command with PATH support
 * @command: user input
 * @program_name: name of shell program for error prints
 */
void execute_command(char *command, char *program_name)
{
	char *args[100];
	char *cmd_copy = strdup(command);
	char *token;
	int i = 0;
	char *path, *path_copy, *dir;
	char full_path[1024];
	pid_t pid;
	int found = 0;

	/* split input to args[] */
	token = strtok(cmd_copy, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* case: absolute/relative path command */
	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(args[0], args, environ);
				perror(program_name);
				free(cmd_copy);
				exit(1);
			}
			wait(NULL);
			free(cmd_copy);
			return;
		}
		dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
		free(cmd_copy);
		return;
	}

	/* search in PATH */
	path = getenv("PATH");
	if (!path)
	{
		free(cmd_copy);
		return;
	}

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);

	if (!found)
	{
		dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
		free(cmd_copy);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror(program_name);
		free(cmd_copy);
		exit(1);
	}

	wait(NULL);
	free(cmd_copy);
}
