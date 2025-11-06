#include "main.h"

/* Split input line by space/tab */
char **tokenize(const char *line)
{
    char *copy, *tok, **argv = NULL;
    size_t cap = 0, len = 0, i;
    char **tmp;

    if (!line)
        return (NULL);

    copy = strdup(line);
    if (!copy)
        return (NULL);

    tok = strtok(copy, " \t");
    while (tok)
    {
        if (len + 2 > cap)
        {
            size_t newcap = cap ? cap * 2 : 8;
            tmp = realloc(argv, newcap * sizeof(char *));
            if (!tmp)
            {
                for (i = 0; i < len; i++)
                    free(argv[i]);
                free(argv);
                free(copy);
                return (NULL);
            }
            argv = tmp;
            cap = newcap;
        }
        argv[len] = strdup(tok);
        len++;
        tok = strtok(NULL, " \t");
    }

    if (!argv)
    {
        free(copy);
        return (NULL);
    }

    argv[len] = NULL;
    free(copy);
    return (argv);
}
