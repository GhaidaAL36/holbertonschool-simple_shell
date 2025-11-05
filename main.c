#include "simple_shell.h"

/**
 * main - Entry point of the simple shell program.
 * @argc: Argument count (unused).
 * @argv: Argument vector.
 * Return: Always 0.
 */
int main(int argc __attribute__((unused)), char *argv[])
{
    char *input = NULL, *trimmed_input;
    size_t len = 0;
    ssize_t nread;

    if (isatty(STDIN_FILENO))
        print_prompt();

    while ((nread = read_input(&input, &len)) != -1)
    {
        if (nread > 0 && input[nread - 1] == '\n')
            input[nread - 1] = '\0';

        trimmed_input = trim_whitespace(input);

        if (strcmp(trimmed_input, "exit") == 0)
        {
            free(input);
            return (0);
        }

        if (trimmed_input[0] != '\0')
            execute_command(trimmed_input, argv[0]);

        if (isatty(STDIN_FILENO))
            print_prompt();
    }

    free(input);
    return (0);
}
