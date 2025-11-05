#include "simple_shell.h"

/**
 * execute_command - Execute a command with PATH support
 * @command: input command from user
 * @program_name: shell name for error messages
 */
void execute_command(char *command, char *program_name)
{
	char *args[64];
	char *cmd_copy, *token;
	int i = 0;
	char *path, *path_copy, *dir;
	char full_path[1024];
	int found = 0;
	pid_t pid;

	/* Make a SAFE copy of command (DO NOT modify original) */
	cmd_copy = strdup(command);

	/* tokenize into args[] */
	token = strtok(cmd_copy, " ");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Case 1: absolute/relative path (contains /) */
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

	/* Case 2: search PATH */
	path = getenv("PATH");
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
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

	/* Execute if found */
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
