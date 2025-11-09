#include "main.h"

/**
	* get_path_copy - returns a strdup copy of PATH
	*
	* Return: pointer to strdup copy of PATH, or NULL if PATH empty
	*/
char *get_path_copy(void)
{
	char *path = getenv("PATH");

	if (!path || path[0] == '\0')
	return (NULL);
	return (strdup(path));
}

/**
	* find_in_path - searches command in path directories
	* @command: command name
	* @path_copy: copy of PATH string
	*
	* Return: full path if found, NULL otherwise
	*/
char *find_in_path(char *command, char *path_copy)
{
	char *dir;
	char full_path[1024];

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
	snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
	if (access(full_path, X_OK) == 0)
	return (strdup(full_path));
	dir = strtok(NULL, ":");
	}
	return (NULL);
}

/**
	* resolve_path - resolves the full path of a command
	* @args: array of command arguments, first element is the command
	* @program_name: name of the shell program
	*
	* This function checks if the command exists and is executable.
	* If the command is not an absolute path, it searches through
	* directories in PATH. If found, args[0] is replaced with the full path.
	* Otherwise, it prints an error and sets args[0] to NULL.
	*
	* Return: 1 if the command is found and executable, 0 otherwise
	*/
int resolve_path(char **args, char *program_name)
{
	char *path_copy, *full_path;

	if (access(args[0], X_OK) == 0)
	return (1);

	path_copy = get_path_copy();
	if (!path_copy)
	{
	dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
	args[0] = NULL;
	return (0);
	}

	full_path = find_in_path(args[0], path_copy);
	free(path_copy);

	if (full_path)
	{
		args[0] = full_path;
	return (1);
	}

	dprintf(STDERR_FILENO, "%s: %s: not found\n", program_name, args[0]);
	args[0] = NULL;
	return (0);
}


