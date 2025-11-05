#include "simple_shell.h"

char *read_line(void)
{
	char *buf = NULL;
	size_t size = 0;
	ssize_t r = 0, i = 0;
	char c;

	buf = malloc(1024);
	if (!buf)
		return (NULL);

	while ((r = read(STDIN_FILENO, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		buf[i++] = c;
	}
	buf[i] = '\0';
	if (r == 0 && i == 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char **split_line(char *line)
{
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
