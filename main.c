#include "main.h"

/**
 * main - simple shell
 * Return: 0 on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    char **args;
    ssize_t nread;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            free(line);
            exit(0);
        }

        args = tokenize(line);
        if (args && args[0])
            execute(args);

        free_tokens(args);
    }

    return (0);
}
