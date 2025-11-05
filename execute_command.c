#include "simple_shell.h"

/**
 * execute_command - Executes a command entered by the user.
 * @command: Command string input by user
 * @program_name: Name of the shell program
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

	/* Parse command + arguments */
	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Built-in exit handled in main already */

	/* If command contains '/' execute directly */
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
		return; /* ❗no fork if not found */
	}

	/* Execute */
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror(program_name);
		exit(1);
	}
	wait(NULL);
}
