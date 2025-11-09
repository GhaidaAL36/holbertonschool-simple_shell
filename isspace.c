#include "main.h"

/**
	* _isspace - checks if a string contains only whitespace characters
	* @str: the string to check
	*
	* Return: 1 if the string is NULL or only spaces/tabs/newlines,
	*         0 if any other character is found
	*/
int _isspace(char *str)
{
	int i = 0;

	if (!str)
	return (1);

	while (str[i])
	{
	if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
	return (0);
	i++;
	}
	return (1);
}
