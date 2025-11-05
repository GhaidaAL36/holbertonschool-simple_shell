#include "main.h"

char **get_argument(char *line)
{
	char **args, *token;
	int bufsize = 64, i = 0;

	args = malloc(sizeof(char *) * bufsize);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		args[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, sizeof(char *) * bufsize);
			if (!args)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;
	return (args);
}

void free_args(char **args)
{
	if (!args)
		return;
	free(args);
}
