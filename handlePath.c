#include "main.h"

/**
 * get_path_env - Get PATH variable from environment
 *
 * Return: Copy of PATH value or NULL
 */
char *get_path_env(void)
{
	int i = 0;
	char *cache, *token;

	while (environ[i] != NULL)
	{
		cache = strdup(environ[i]);
		if (!cache)
			return (NULL);

		token = strtok(cache, "=");
		if (token && strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			if (token)
			{
				token = strdup(token);
				free(cache);
				return (token);
			}
		}

		free(cache);
		i++;
	}

	return (NULL);
}

/**
 * build_full_path - Create full path from directory + command
 * @dir: Directory
 * @cmd: Command
 *
 * Return: Allocated full path or NULL
 */
char *build_full_path(char *dir, char *cmd)
{
	char *result;

	result = malloc(strlen(dir) + strlen(cmd) + 2);
	if (result == NULL)
		return (NULL);

	sprintf(result, "%s/%s", dir, cmd);
	return (result);
}

/**
 * handle_path - Resolve full path of a command
 * @input: Command
 *
 * Return: Full path or NULL
 */
char *handle_path(char *input)
{
	char *path_env, *token, *full;

	if (strchr(input, '/'))
		return (strdup(input));

	path_env = get_path_env();
	if (!path_env)
		return (NULL);

	token = strtok(path_env, ":");
	while (token)
	{
		full = build_full_path(token, input);
		if (!full)
		{
			free(path_env);
			return (NULL);
		}

		if (access(full, X_OK) == 0)
		{
			free(path_env);
			return (full);
		}

		free(full);
		token = strtok(NULL, ":");
	}

	free(path_env);
	return (NULL);
}
