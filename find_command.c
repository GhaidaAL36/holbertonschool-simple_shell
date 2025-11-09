#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
	* try_cmd_path - checks if cmd exists in a given directory
	* @dir: directory path
	* @cmd: command name
	*
	* Return: full path string (malloced) if executable, NULL otherwise
	*/
char *try_cmd_path(char *dir, char *cmd)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);

	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
	* cmd_with_slash - checks if cmd contains '/' and is executable
	* @cmd: command
	*
	* Return: malloced path if executable, NULL otherwise
	*/
char *cmd_with_slash(char *cmd)
{
	char *full_path;

	if (!cmd || !strchr(cmd, '/'))
		return (NULL);

	if (access(cmd, X_OK) != 0)
		return (NULL);

	full_path = malloc(strlen(cmd) + 1);
	if (!full_path)
		return (NULL);

	strcpy(full_path, cmd);
	return (full_path);
}

/**
	* find_command - finds the full path of a command
	* @cmd: the command to find
	* @envp: environment variables
	*
	* Return: full path string (malloced) or NULL if not found
	*/
char *find_command(char *cmd, char **envp)
{
	char *path_env, *path_dup, *dir, *full_path;

	if (!cmd)
		return (NULL);

	full_path = cmd_with_slash(cmd);
	if (full_path)
		return (full_path);

	path_env = get_path_env(envp);
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_dup = malloc(strlen(path_env) + 1);
	if (!path_dup)
		return (NULL);
	strcpy(path_dup, path_env);

	dir = strtok(path_dup, ":");
	while (dir)
	{
		full_path = try_cmd_path(dir, cmd);
		if (full_path)
		{
			free(path_dup);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}

