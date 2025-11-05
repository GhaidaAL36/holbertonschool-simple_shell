#include "simple_shell.h"

/**
 * main - Entry point of simple shell
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		line = read_input();
		if (!line)
			break;

		trim_whitespace(line);
		args = parse_line(line);
		if (!args || !args[0])
		{
			free(args);
			free(line);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			break;
		}

		execute_command(args, env);
		free(args);
		free(line);
	}
	return (0);
}
