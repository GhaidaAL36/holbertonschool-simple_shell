#include "main.h"

/**
 * find_path - search command in PATH
 * @command: command name
 * Return: full path or NULL if not found
 */
char *find_path(char *command)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *full_path;
    size_t len;

    if (!path)
        return (NULL);

    if (access(command, X_OK) == 0)
        return (strdup(command));

    path_copy = strdup(path);
    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = strlen(dir) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
            break;

        snprintf(full_path, len, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
