#include "simple_shell.h"

int main(void)
{
	char *line;
	char **args;
	pid_t pid;
	int status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		line = read_line();
		if (!line)
			break;

		args = split_line(line);
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

		pid = fork();
		if (pid == 0)
			execute_command(args);
		else
			waitpid(pid, &status, 0);

		free(args);
		free(line);
	}
	return (0);
}
