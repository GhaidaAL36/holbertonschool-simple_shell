#include "main.h"

/**
	* get_path - retrieves the PATH variable from environ
	* Return: pointer to PATH string, or NULL if not found
	*/
char *get_path(void)
{
	int i = 0;

	while (environ[i])
	{
	if (strncmp(environ[i], "PATH=", 5) == 0)
	return (environ[i] + 5);
	i++;
	}
	return (NULL);
}

/**
	* resolve_path - finds full path of command
	* @args: array of arguments, args[0] is the command
	* @program_name: name of the shell (for errors)
	* Return: 1 if found and executable, 0 if not found
	*/
int resolve_path(char **args, char *program_name)
{
	char *path_copy, *dir, full_path[1024];
	char *path;

	if (access(args[0], X_OK) == 0)
	return (1);

	path = get_path();
	if (!path || path[0] == '\0')
	{
	args[0] = NULL;
	return (0);
	}

	path_copy = strdup(path);
	if (!path_copy)
	return (0);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
	snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
	if (access(full_path, X_OK) == 0)
	{
	args[0] = strdup(full_path);
	free(path_copy);
	return (1);
	}
	dir = strtok(NULL, ":");
	}

	free(path_copy);
	dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
	args[0] = NULL;
	return (0);
}

