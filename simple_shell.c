#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
extern char **environ;

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
	char *args[200];
	pid_t pid;
	char *token;
	int i = 0;
	
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];
	int found = 0;
	
	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;
	if (access(args[0], X_OK) != 0)
	{
		path = getenv("PATH");
		path_copy = strdup(path);
		dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
			if (access(full_path, X_OK) == 0)
			{
				args[0] = strdup(full_path);
				found = 1;
				break;
			}
			dir = strtok(NULL, ":");
		}
		free(path_copy);
		if (!found)
{
	dprintf(STDERR_FILENO, "hsh: %s: not found\n", args[0]);
	return;
}

	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}

	if (pid == 0)
	{
		    if (execve(args[0], args, environ) == -1)
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
 * trim_whitespace - Removes leading and trailing spaces from a string
 * @str: The string to trim
 * Return: pointer to the trimmed string
 */
char *trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return str;
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
	char *trimmed_input;

	if (isatty(STDIN_FILENO))
		print_prompt();

	nread = read_input(&input, &len);

	while (nread != -1)
	{
		if (input[nread - 1] == '\n')
			input[nread - 1] = '\0';

		trimmed_input = trim_whitespace(input);

/*  Handle exit built-in */
if (strcmp(trimmed_input, "exit") == 0)
{
    free(input);  /* مهم جداً عشان ما يصير memory leak */
    return 0;     /* خروج نظيف */
}

if (trimmed_input[0] != '\0')
    execute_command(trimmed_input, argv[0]);


		if (isatty(STDIN_FILENO))
			print_prompt();

		nread = read_input(&input, &len);
	}

	free(input);
	return (0);
}
