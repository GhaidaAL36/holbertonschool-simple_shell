#include "main.h"

/**
 * handle_path - Find the full path of a command
 * @input: User input command
 *
 * Return: Full path if found, otherwise NULL
 */
char *handle_path(char *input)
{
	int i = 0;
	char *cache, *token, *result;

	if (strchr(input, '/') != NULL)
		return (strdup(input));

	while (environ[i] != NULL)
	{
		cache = strdup(environ[i]);
		if (cache == NULL)
			return (NULL);

		token = strtok(cache, "=");
		if (token != NULL && strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			token = strtok(token, ":");

			while (token != NULL)
			{
				result = malloc(strlen(token) + strlen(input) + 2);
				if (result == NULL)
				{
					free(cache);
					return (NULL);
				}

				sprintf(result, "%s/%s", token, input);

				if (access(result, X_OK) == 0)
				{
					free(cache);
					return (result);
				}

				free(result);
				token = strtok(NULL, ":");
			}
		}

		free(cache);
		i++;
	}

	free(input);
	return (NULL);
}
