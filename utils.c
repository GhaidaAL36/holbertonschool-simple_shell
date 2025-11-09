#include "main.h"

/**
	* _isspace - checks if a string contains only spaces or tabs
	* @s: input string
	* Return: 1 if only spaces/tabs, 0 otherwise
	*/
int _isspace(char *s)
{
	int i = 0;

	if (!s)
		return (1);

	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

