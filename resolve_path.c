#include "main.h"

/**
	* resolve_path - Finds the full executable path for a command if needed.
	* Return: 1 if found or command already valid, 0 if not found.
	*/
int resolve_path(char **args, char *program_name)
{
	char *path, *path_copy, *dir;
	char full_path[1024];

	if (access(args[0], X_OK) == 0)
	return (1);

	path = getenv("PATH");
	if (!path || path[0] == '\0')
	{
	dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
	return (0);
	}

	path_copy = strdup(path);
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

