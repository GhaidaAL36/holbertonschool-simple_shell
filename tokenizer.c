#include "main.h"

/**
 * tokenize - split line into tokens
 * @line: input line
 * Return: array of tokens
 */
char **tokenize(char *line)
{
    char **tokens;
    char *token;
    int i = 0;

    tokens = malloc(sizeof(char *) * 64);
    if (!tokens)
        return (NULL);

    token = strtok(line, " \t\n");
    while (token)
    {
        tokens[i] = strdup(token);
        i++;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL;
    return (tokens);
}

/**
 * free_tokens - free tokenized array
 * @tokens: array to free
 */
void free_tokens(char **tokens)
{
    int i;

    for (i = 0; tokens[i]; i++)
        free(tokens[i]);
    free(tokens);
}
