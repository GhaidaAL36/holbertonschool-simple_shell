#include "main.h"

/**
 * handle_logical_operators - Handles && and || logical operators
 * @line: input line
 * @env: environment variables
 * Return: last command status
 */
int handle_logical_operators(char *line, char **env)
{
	char *token, *rest;
	int status = 0;
	int run_next = 1; /* 1 = run */

	token = strtok_r(line, ";", &rest);
	while (token)
	{
		if (_strstr(token, "&&"))
		{
			char *cmd1 = strtok(token, "&");
			char *cmd2 = strtok(NULL, "&");

			if (cmd1)
				status = execute_command_line(cmd1, env);
			if (status == 0 && cmd2)
				status = execute_command_line(cmd2, env);
		}
		else if (_strstr(token, "||"))
		{
			char *cmd1 = strtok(token, "|");
			char *cmd2 = strtok(NULL, "|");

			if (cmd1)
				status = execute_command_line(cmd1, env);
			if (status != 0 && cmd2)
				status = execute_command_line(cmd2, env);
		}
		else
		{
			if (run_next)
				status = execute_command_line(token, env);
		}
		token = strtok_r(NULL, ";", &rest);
	}
	return (status);
}
