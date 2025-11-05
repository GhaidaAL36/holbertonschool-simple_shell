#include "main.h"

/**
 * main - Simple shell that handles PATH
 */
int main(void)
{
    char *line = NULL;
    char **args = NULL;
    ssize_t read;
    size_t len = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            free(line);
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (line[0] == '\n')
            continue;

        line[read - 1] = '\0';
        args = tokenize(line);
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

        execute(args);
        free_args(args);
    }

    free(line);
    return (0);
}
