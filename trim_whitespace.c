#include "simple_shell.h"

/**
 * trim_whitespace - removes leading and trailing whitespace
 * @str: input string
 */
void trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';
}
