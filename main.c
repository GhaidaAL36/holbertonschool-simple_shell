#include "main.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: last command exit status
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *command;
	char *args[100];
	int status = 0;

	(void)argc;
	(void)argv;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = _getline(&line, &len);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (_strstr(line, "&&") || _strstr(line, "||"))
		{
			handle_logical_operators(line, envp);
			continue;
		}

		command = trim(line);
		if (!_isspace(command))
		{
			parse_command(command, args);

			if (handle_builtins(args, line, envp, &status))
				continue;

			status = execute_command(args, envp);
		}
	}

	free(line);
	return (status);
}
