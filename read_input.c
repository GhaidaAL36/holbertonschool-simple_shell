#include "simple_shell.h"

/**
 * read_line - reads a line from stdin using read()
 * Return: pointer to the line
 */
char *read_line(void)
{
	char *buffer;
	size_t bufsize = 1024;
	ssize_t bytes_read;
	size_t i = 0;
	char c;

	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (NULL);

	while (1)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0 || c == '\n')
		{
			buffer[i] = '\0';
			return (buffer);
		}
		buffer[i++] = c;
		if (i >= bufsize)
		{
			bufsize += 1024;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return (NULL);
		}
	}
}
