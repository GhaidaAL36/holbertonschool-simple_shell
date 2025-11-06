#include "main.h"

/**
 * print_env - prints all environment variables
 * Return: 0
 */
int print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 * parse - split command line and execute
 * @command: user input
 * @envp: environment pointer (unused)
 */
void parse(char command[], char **envp)
{
	char *args[64];
	char *token;
	int i = 0;

	(void) envp;
	token = strtok(command, " \t\n");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0])
	{
		if (strcmp(args[0], "exit") == 0)
			exit(0);
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			return;
		}
		execute(args, environ);
	}
}

/**
 * main - simple shell main loop
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &size, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}
		if (nread > 1)
			parse(line, environ);
	}
	free(line);
	return (0);
}
