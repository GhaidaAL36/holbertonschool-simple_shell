#include "main.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	char **args = NULL;
	size_t len = 0;
	ssize_t read_len;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read_len = getline(&line, &len, stdin);
		if (read_len == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] == '\n' || line[0] == '\0')
			continue;

		line[read_len - 1] = '\0';

		args = get_argument(line);
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		if (_strcmp(args[0], "exit") == 0)
		{
			free_args(args);
			break;
		}

		if (_strcmp(args[0], "env") == 0)
		{
			print_env();
			free_args(args);
			continue;
		}

		execute_command(args);
		free_args(args);
	}

	free(line);
	return (0);
}
