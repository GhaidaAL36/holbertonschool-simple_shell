#include "main.h"

int main(void)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;
    char **argv;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        nread = getline(&line, &size, stdin);
        if (nread == -1)
            break;

        if (line[0] != '\n')
        {
            argv = tokenize(line);
            execute(argv);
            free(argv);
        }
    }

    free(line);
    return (0);
}
