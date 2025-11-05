#include "simple_shell.h"
#include <unistd.h>
extern char **environ;

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to execute (e.g., "/bin/ls").
 * @program_name: The name of the shell program (for error messages).
 */
void execute_command(char *command, char *program_name)
{
	char *args[200];
	pid_t pid;
	char *token;
	int i = 0;

	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];
	int found = 0;

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;
	if (access(args[0], X_OK) != 0)
	{
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
		if (!found)
{
	dprintf(STDERR_FILENO, "hsh: %s: not found\n", args[0]);
	return;
}
	}
	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}

	if (pid == 0)
	{
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
}
