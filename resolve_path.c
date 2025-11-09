#include "main.h"

/**
 * resolve_path - resolves the full path of a command
 * @args: array of command arguments, first element is the command
 * @program_name: name of the shell program
 *
 * This function checks if the command exists and is executable.
 * If not an absolute path, it searches through directories in PATH.
 * If found, args[0] is replaced with the full path.
 * Otherwise, prints an error message.
 *
 * Return: 1 if the command is found and executable, 0 otherwise
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

