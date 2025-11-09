#include "main.h"

/**
	* trim_whitespace - Removes leading and trailing spaces from a string.
	* @str: Input string.
	*
	* Return: Pointer to trimmed string.
	*/
char *trim_whitespace(char *str)
{
	char *end;

	/* skip leading spaces */
	while (*str == ' ' || *str == '\t' || *str == '\n')
	str++;

	if (*str == '\0')
	return (str);

	/* remove trailing spaces */
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
	end--;

	*(end + 1) = '\0';
	return (str);
}
