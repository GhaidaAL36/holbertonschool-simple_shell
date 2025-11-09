#include "main.h"

/**
	* main - simple UNIX command line interpreter
	* @argc: argument count
	* @argv: argument vector
	* @envp: environment variables
	* Return: 0 on success
	*/
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	(void)argc;

	while (1)
	{
		/* Print prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove trailing newline */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Ignore empty lines or spaces only */
		if (_isspace(line))
			continue;

		pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			continue;
		}
		if (pid == 0)
		{
			char *args[2];

			args[0] = line;
			args[1] = NULL;

			if (execve(line, args, envp) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}

	free(line);
	return (0);
}

