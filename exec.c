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
 * pathfinder - Find executable file in PATH
 * @cmd: Command
 * @command: Command array
 * Return: Modified argv or NULL
 */
char **pathfinder(char *cmd, char **command)
{
	char *path = _getenv("PATH"), *path_copy, *dir, full[512];

	if (!path)
		return (NULL);

	if (access(cmd, X_OK) == 0)
	{
		command[0] = cmd;
		return (command);
	}

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full, sizeof(full), "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			command[0] = strdup(full);
			free(path_copy);
			return (command);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute - Execute a command
 * @command: Command array
 * @envp: Environment variables
 * Return: 0 on success
 */
int execute(char **command, char **envp)
{
	pid_t pid;
	int status;
	char *full_path = NULL;

	(void) envp;
	pathfinder(command[0], command);

	if (access(command[0], X_OK) != 0)
	{
		write(STDERR_FILENO, command[0], strlen(command[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	if (strchr(command[0], '/'))
		full_path = command[0];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (full_path && full_path != command[0])
			free(full_path);
		return (1);
	}
	if (pid == 0)
	{
		execve(command[0], command, environ);
		perror(command[0]);
		_exit(2);
	}
	else
		waitpid(pid, &status, 0);

	if (full_path && full_path != command[0])
		free(full_path);
	return (0);
}
