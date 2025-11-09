#include "main.h"

/**
	* parse_command - tokenizes a command line into arguments
	* @line: input line
	* @args: array to store tokens
	*
	* Return: number of arguments
	*/
int parse_command(char *line, char *args[])
{
	char *token;
	int i = 0;

	token = strtok(line, " \t\n");
	while (token && i < 99)
	{
	args[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}

