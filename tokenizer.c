#include "main.h"

char **tokenize(char *line)
{
    char **argv;
    char *token;
    int i = 0;

    argv = malloc(sizeof(char *) * 64);
    if (!argv)
        return (NULL);

    token = strtok(line, " \t\n");
    while (token)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[i] = NULL;
    return (argv);
}
