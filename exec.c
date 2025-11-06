#include "main.h"

/**
 * _getenv - get environment variable value
 * @name: variable name
 * Return: pointer to value or NULL
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
 * pathfinder - locate executable in PATH
 * @cmd: command name
 * @command: argv array
 * Return: updated argv or NULL
 */
char **pathfinder(char *cmd, char **command)
{
	char *path = _getenv("PATH");
	char *dir, *dup, *full;
	int len;

	if (access(cmd, X_OK) == 0)
	{
		command[0] = cmd;
		return (command);
	}

	if (!path)
		return (NULL);

	dup = strdup(path);
	dir = strtok(dup, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(dup);
			return (NULL);
		}
		sprintf(full, "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			command[0] = full;
			free(dup);
			return (command);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(dup);
	return (NULL);
}

/**
 * execute - execute a given command
 * @command: argv array
 * @envp: environment (unused)
 * Return: 0 on success
 */
int execute(char *const command[], char **envp)
{
	pid_t pid;
	int status;
	char **temp;
	char *to_free = NULL;

	(void) envp;
	temp = pathfinder(command[0], (char **) command);
	if (!temp)
	{
		write(STDERR_FILENO, command[0], strlen(command[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	if (temp[0] != command[0])
		to_free = temp[0];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (to_free)
			free(to_free);
		return (1);
	}
	if (pid == 0)
	{
		execve(temp[0], (char *const *)command, environ);
		perror(command[0]);
		if (to_free)
			free(to_free);
		_exit(2);
	}
	else
		waitpid(pid, &status, 0);

	if (to_free)
		free(to_free);
	return (0);
}
