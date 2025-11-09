#include "main.h"

/**
	* handle_exit - exits the shell if command is "exit"
	* @args: array of command arguments
	* @line: input line to free
	* @status: current exit status
	*
	* Return: void (exits the program if "exit" is called)
	*/
void handle_exit(char *args[], char *line, int status)
{
	if (strcmp(args[0], "exit") == 0)
	{
	free(line);
	exit(status);
	}
}
