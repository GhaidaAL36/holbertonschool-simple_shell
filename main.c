#include "simple_shell.h"

/**
 * main - Entry point of simple shell
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
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

		if (_strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			break;
		}

		pid = fork();
		if (pid == 0)
			execute_command(args);
		else if (pid > 0)
			waitpid(pid, &status, 0);
		else
			perror("fork");

		free(args);
		free(line);
	}
	return (0);
}
