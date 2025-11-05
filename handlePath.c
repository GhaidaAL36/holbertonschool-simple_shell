#include "main.h"

/**
 * find_in_path - search command in PATH
 * @cmd: command name
 * Return: full path string (malloc'd) or NULL if not found
 */
char *find_in_path(const char *cmd)
{
	char *path = getenv("PATH"), *copy, *token, full[1024];
	struct stat st;

	if (!cmd || !path)
		return (NULL);

	copy = malloc(strlen(path) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, path);

	token = strtok(copy, ":");
	while (token)
	{
		strcpy(full, token);
		strcat(full, "/");
		strcat(full, cmd);
		if (stat(full, &st) == 0)
		{
			free(copy);
			return (strdup(full));
		}
		token = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
