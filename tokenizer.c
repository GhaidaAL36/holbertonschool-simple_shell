#include "main.h"

/**
 * tokenize - split command line into arguments
 */
char **tokenize(char *line)
{
    char **args = NULL;
    char *token = NULL;
    int i = 0;

    args = malloc(sizeof(char *) * 64);
    if (!args)
        return (NULL);

    token = strtok(line, " \t\r\n");
    while (token)
    {
        args[i] = strdup(token);
        i++;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
    return (args);
}

/**
 * free_args - free memory
 */
void free_args(char **args)
{
    int i;

    if (!args)
        return;

    for (i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}
