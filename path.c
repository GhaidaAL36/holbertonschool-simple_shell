#include "main.h"

char *find_path(char *cmd)
{
    char *path = NULL, *dir = NULL, *dup = NULL, *full = NULL;
    int len;

    if (access(cmd, X_OK) == 0)
        return (strdup(cmd));

    for (int i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5;
            break;
        }
    }

    if (!path)
        return (NULL);

    dup = strdup(path);
    if (!dup)
        return (NULL);

    dir = strtok(dup, ":");
    while (dir)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full = malloc(len);
        if (!full)
        {
            free(dup);
            return (NULL);
        }

        sprintf(full, "%s/%s", dir, cmd);
        if (access(full, X_OK) == 0)
        {
            free(dup);
            return (full);
        }

        free(full);
        dir = strtok(NULL, ":");
    }

    free(dup);
    return (NULL);
}
