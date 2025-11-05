#include "simple_shell.h"
#include <unistd.h>
extern char **environ;

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to execute (e.g., "/bin/ls").
 * @program_name: The name of the shell program (for error messages).
 * execute_command - Execute a command entered by the user
 * @command: The full input string from user
 * @args: Parsed command and arguments (args[0] = command)
 * @program_name: Name of the shell program
 *
 * Return: Nothing
 */
void execute_command(char *command, char *program_name)
void execute_command(char *command, char **args, char *program_name)
{
	char *args[200];
	pid_t pid;
	char *token;
	int i = 0;

	char *path;
	char *path_copy;
	char *dir;
	char *path, *path_copy, *dir;
	char full_path[1024];
	int found = 0;
	pid_t pid;

	token = strtok(command, " ");
	while (token != NULL)
	/* Built-in: exit */
	if (strcmp(args[0], "exit") == 0)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
		free(command);
		exit(0);
	}

	args[i] = NULL;
	if (access(args[0], X_OK) != 0)
	/* If command contains '/', try executing directly */
	if (strchr(args[0], '/') != NULL)
	{
		path = getenv("PATH");
		path_copy = strdup(path);
		dir = strtok(path_copy, ":");

		while (dir != NULL)
		if (access(args[0], X_OK) == 0)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
			if (access(full_path, X_OK) == 0)
			pid = fork();
			if (pid == 0)
			{
				args[0] = strdup(full_path);
				found = 1;
				break;
				execve(args[0], args, environ);
				perror(program_name);
				exit(1);
			}
			dir = strtok(NULL, ":");
			wait(NULL);
			return;
		}
		if (!found)
{
    dprintf(STDERR_FILENO, "hsh: %s: not found\n", args[0]);
    exit(127);
}
		dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
		return;
	}
	pid = fork();

	if (pid == -1)
	/* Search PATH for command */
	path = getenv("PATH");
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		perror("fork failed");
		exit(1);
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
		if (execve(args[0], args, environ) == -1)
		{
			perror(program_name);
			exit(1);
		}
	}

	else
	{
		wait(NULL);
	}
	wait(NULL);
}
