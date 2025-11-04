#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * print_prompt - Prints the shell prompt to the user.
 */
void print_prompt(void)
{
	printf("$: ");
}

/**
 * read_input - Reads a line of input from the user.
 * @input: Pointer to the buffer that stores user input.
 * @len: Pointer to the size of the buffer.
 *
 * Return: Number of characters read, or -1 on failure.
 */
ssize_t read_input(char **input, size_t *len)
{
	return (getline(input, len, stdin));
}

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to execute (e.g., "/bin/ls").
 * @program_name: The name of the shell program (for error messages).
 */
void execute_command(char *command, char *program_name)
{
	char *args[2];
	pid_t pid;

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror(program_name);
			exit(1);
		}
	}

	else
	{
		wait(NULL);
	}
}

/**
 * main - Entry point of the simple shell program.
 * @argc: Argument count.
 * @argv: Argument vector (array of strings).
 *
 * Return: Always 0.
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nread;

	if (isatty(STDIN_FILENO))
		print_prompt();

	nread = read_input(&input, &len);

	while (nread != -1)
	{
		if (input[nread - 1] == '\n')
			input[nread - 1] = '\0';

		execute_command(input, argv[0]);

		if (isatty(STDIN_FILENO))
			print_prompt();

		nread = read_input(&input, &len);
	}

	free(input);
	return (0);
}
