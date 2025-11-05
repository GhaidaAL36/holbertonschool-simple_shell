#include "main.h"

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		exit(0);
	}
	return (line);
}

char **tokenize(char *line)
{
	char **tokens, *token;
	int i = 0;
	size_t size = 64;

	tokens = malloc(size * sizeof(char *));
	if (!tokens)
		exit(1);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

int main(void)
{
	char *line, **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		args = tokenize(line);
		if (!args[0])
		{
			free(line);
			free(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			break;
		}
		execute(args);
		free(line);
		free(args);
	}
	return (0);
}
