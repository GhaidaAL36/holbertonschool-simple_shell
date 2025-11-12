#include "main.h"

/**
 * _getline - Reads a line from standard input
 * @lineptr: Pointer to buffer that will store the input line
 * @n: Pointer to size of buffer
 *
 * Return: Number of characters read (including '\n'), or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t bytes_read = 0, total = 0;
	char buffer[1024];
	char *new_lineptr;
	size_t new_size;
	int i;

	if (lineptr == NULL || n == NULL)
		return (-1);

	/* Allocate initial buffer if needed */
	if (*lineptr == NULL || *n == 0)
	{
		*n = 1024;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (bytes_read <= 0)
			return (total > 0 ? total : -1);

		for (i = 0; i < bytes_read; i++)
		{
			if (total + 1 >= *n)
			{
				new_size = *n * 2;
				new_lineptr = realloc(*lineptr, new_size);
				if (new_lineptr == NULL)
					return (-1);
				*lineptr = new_lineptr;
				*n = new_size;
			}

			(*lineptr)[total++] = buffer[i];

			if (buffer[i] == '\n')
			{
				(*lineptr)[total] = '\0';
				return (total);
			}
		}
	}
}
