#include "main.h"

int main(void)
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t n;
    char **argv;
    size_t i;

    while (1)
    {
        if (is_interactive())
            write(STDOUT_FILENO, "$ ", 2);

        n = getline(&line, &cap, stdin);
        if (n == -1)
            break;

        trim_ends(line);
        if (!*line || is_empty(line))
            continue;

        argv = tokenize(line);
        if (argv)
        {
            exec_command(argv);
            for (i = 0; argv[i]; i++)
                free(argv[i]);
            free(argv);
        }
    }

    free(line);
    return (0);
}
