#include "main.h"

/**
 * _strstr - Finds substring in a string
 * @haystack: the big string
 * @needle: substring to find
 * Return: pointer to first occurrence or NULL
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j;

	for (i = 0; haystack[i]; i++)
	{
		for (j = 0; needle[j] && haystack[i + j] == needle[j]; j++)
			;
		if (!needle[j])
			return (&haystack[i]);
	}
	return (NULL);
}
