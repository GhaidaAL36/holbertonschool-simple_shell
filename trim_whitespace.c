#include "simple_shell.h"

/**
 * trim_whitespace - Removes leading and trailing spaces from a string
 * @str: The string to trim
 * Return: pointer to the trimmed string
 */
char *trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return str;
}
