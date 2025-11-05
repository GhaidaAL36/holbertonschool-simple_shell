#include "simple_shell.h"

/* get PATH from environ manually */
char *get_path_from_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return environ[i] + 5;
		i++;
	}
	return (NULL);
}

/**
 * execute_command - Execute a command with PATH support
 * @command: input line
 * @program_name: shell name for errors
 */
void execute_command(char *command, char *program_name)
{
	char *args[64];
	char *cmd_copy = strdup(command);
	char *token;
	int i = 0;
	char *path, *path_copy, *dir;
	char full_path[1024];
	int found = 0;
	pid_t pid;

	/* tokenize safely (do NOT modify original command) */
	token = strtok(cmd_copy, " ");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* if command has '/', try direct exec */
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

	/* PATH lookup using environ (NOT getenv) */
	path = get_path_from_env();
	if (!path)
	{
		free(cmd_copy);
		return;
	}
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

	/* execute */
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
