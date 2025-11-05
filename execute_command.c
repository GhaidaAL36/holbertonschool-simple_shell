#include "simple_shell.h"

/**
 * execute_command - Execute a command with arguments and PATH support
 * @command: full input string
 * @program_name: program name for error messages
 */
void execute_command(char *command, char *program_name)
{
	char *args[100];
	char *token;
	int i = 0;
	char *path, *path_copy, *dir;
	char full_path[1024];
	int found = 0;
	pid_t pid;

	/* Split input to arguments */
	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* If command contains a '/' try direct exec first */
	if (strchr(args[0], '/') != NULL)
	{
		if (access(args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(args[0], args, environ);
				perror(program_name);
				exit(1);
			}
			wait(NULL);
			return;
		}
		dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
		return;
	}

	/* Search in PATH */
	path = getenv("PATH");
	if (!path)
		return;
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
		return;
	}

	/* Execute found command */
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror(program_name);
		exit(1);
	}
	wait(NULL);
}
