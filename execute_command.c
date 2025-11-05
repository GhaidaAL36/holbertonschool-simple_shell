#include "simple_shell.h"

/**
 * execute_command - Execute a command entered by the user
 * @command: The full input string from user
 * @args: Parsed command and arguments (args[0] = command)
 * @program_name: Name of the shell program
 *
 * Return: Nothing
 */
void execute_command(char *command, char **args, char *program_name)
{
	char *path, *path_copy, *dir;
	char full_path[1024];
	int found = 0;
	pid_t pid;

	/* Built-in: exit */
	if (strcmp(args[0], "exit") == 0)
	{
		free(command);
		exit(0);
	}

	/* If command contains '/', try executing directly */
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

	/* Search PATH for command */
	path = getenv("PATH");
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			args[0] = strdup(full_path);
			found = 1;
			break;
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);

	/* If not found in PATH */
	if (!found)
	{
		dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
		return;
	}

	/* Execute */
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(program_name);
			exit(1);
		}
	}
	wait(NULL);
}
