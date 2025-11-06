#include "main.h"

/**
 * _getenv - Get environment variable value
 * @name: Variable name
 * Return: Pointer to value or NULL
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * find_path - Finds the executable full path
 * @cmd: command name
 * Return: malloc'd full path or NULL
 */
char *find_path(char *cmd)
{
	char *path = _getenv("PATH"), *copy, *dir, full[512];

	if (!path)
		return (NULL);

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	copy = strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		snprintf(full, sizeof(full), "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (strdup(full));
		}
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}

/**
 * execute - Executes a command
 * @command: tokenized command
 * @envp: environment
 * Return: 0
 */
int execute(char **command, char **envp)
{
	pid_t pid;
	int status;
	char *full_path;

	(void) envp;

	full_path = find_path(command[0]);
	if (!full_path)
	{
		write(STDERR_FILENO, command[0], strlen(command[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return (1);
	}
	if (pid == 0)
	{
		execve(full_path, command, environ);
		perror(command[0]);
		free(full_path);
		_exit(2);
	}
	else
		waitpid(pid, &status, 0);

	free(full_path);
	return (0);
}
