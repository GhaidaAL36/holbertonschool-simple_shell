#define _GNU_SOURCE
#include "main.h"

/**
 * spacesCheck - Check if a string contains only spaces
 * @str: String to check
 *
 * Return: 1 if only spaces, 0 otherwise
 */
int spacesCheck(const char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
	char *args[64] = {NULL};
	size_t input_size = 0;
	ssize_t input_read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		input_read = getline(&input, &input_size, stdin);

		if (input_read == EOF)
		{
			free(input);
			exit(0);
		}

		if (input_read > 0 && input[input_read - 1] == '\n')
			input[input_read - 1] = '\0';

		if (!spacesCheck(input))
			tokenize(input, args);
	}

	free(input);
	return (0);
}
#include "main.h"

/**
 * main - Simple Shell 0.1
 *
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int status;

	while (1)
	{
		/* Display prompt */
		if (isatty(STDIN_FILENO))
			printf("$ ");

		/* Read input */
		nread = getline(&input, &size, stdin);

		/* Handle Ctrl+D */
		if (nread == -1)
		{
			free(input);
			exit(0);
		}

		/* Remove newline */
		if (input[nread - 1] == '\n')
			input[nread - 1] = '\0';

		/* Ignore empty line */
		if (input[0] == '\0')
			continue;

		/* Check if file exists and executable */
		if (access(input, X_OK) != 0)
		{
			perror("./hsh");
			continue;
		}

		/* Create child process */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			/* Execute command */
			execve(input, NULL, environ);
			perror("./hsh");
			exit(1);
		}
		else
		{
			/* Parent waits */
			waitpid(pid, &status, 0);
		}
	}

	free(input);
	return (0);
}

