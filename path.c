#include "main.h"

/**
 * find_path - find full path for a command using PATH
 */
char *find_path(char *command)
{
    char *path = getenv("PATH");
    char *token, *full_path;
    struct stat st;

    if (!path)
        return (NULL);

    token = strtok(path, ":");
    while (token)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
            return (NULL);

        sprintf(full_path, "%s/%s", token, command);
        if (stat(full_path, &st) == 0)
            return (full_path);

        free(full_path);
        token = strtok(NULL, ":");
    }

    return (NULL);
}
