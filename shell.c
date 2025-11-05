#include "main.h"

int is_interactive(void)
{
    return isatty(STDIN_FILENO);
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t n = getline(&line, &len, stdin);

    if (n == -1)
    {
        free(line);
        return NULL;
    }
    return line;
}

char **tokenize(char *line)
{
    char **args = NULL, *tok;
    size_t cap = 8, i = 0;

    args = malloc(sizeof(char *) * cap);
    if (!args)
        return NULL;

    tok = strtok(line, " \t\r\n");
    while (tok)
    {
        if (i + 1 >= cap)
        {
            cap <<= 1;
            args = realloc(args, sizeof(char *) * cap);
            if (!args)
                return NULL;
        }
        args[i++] = tok;
        tok = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
    return args;
}

int main(void)
{
    char *line, **argv;
    int inter = is_interactive();

    while (1)
    {
        if (inter)
            write(STDOUT_FILENO, "$ ", 2);

        line = read_line();
        if (!line)
            break;

        argv = tokenize(line);
        if (!argv || !argv[0])
        {
            free(argv);
            free(line);
            continue;
        }

        if (strcmp(argv[0], "exit") == 0)
        {
            free(argv);
            free(line);
            break;
        }

        execute(argv);
        free(argv);
        free(line);
    }
    return 0;
}
