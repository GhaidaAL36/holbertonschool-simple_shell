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
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "\n", 1);
	break;
	}

	/* Trim spaces and newline */
	line = trim(line);
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
	char *args[100];
	int i = 0;
	char *token = strtok(line, " \t\n");

	while (token != NULL && i < 99)
	{
	args[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (execve(args[0], args, envp) == -1)
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
