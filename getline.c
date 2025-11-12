#include "main.h"

/**
 * _strlen - Returns the length of a string
 * @s: String
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	while (s && s[i])
		i++;
	return (i);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, positive or negative value if different
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strcpy - Copies a string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strchr - Locates a character in a string
 * @s: String to search
 * @c: Character to find
 * Return: Pointer to first occurrence or NULL
 */
char *_strchr(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
