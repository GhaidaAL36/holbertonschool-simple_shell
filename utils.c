#include "main.h"

/**
	* _strdup - duplicates a string (replacement for strdup)
	* @s: the string to duplicate
	* Return: pointer to new string or NULL
	*/
char *_strdup(const char *s)
{
	char *dup;
	size_t len;

	if (s == NULL)
	return (NULL);

	len = strlen(s) + 1;
	dup = malloc(len);
	if (dup == NULL)
	return (NULL);

	memcpy(dup, s, len);
	return (dup);
}

