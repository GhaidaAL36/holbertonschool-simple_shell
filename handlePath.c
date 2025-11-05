#include "main.h"

char *handle_path(const char *cmd)
{
    char *path = getenv("PATH");
    char *copy, *token, *full;
    struct stat st;

    if (!cmd || !path)
        return NULL;

    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (stat(cmd, &st) == 0)
            return strdup(cmd);
        return NULL;
    }

    copy = strdup(path);
    token = strtok(copy, ":");
    while (token)
    {
        full = malloc(strlen(token) + strlen(cmd) + 2);
        strcpy(full, token);
        strcat(full, "/");
        strcat(full, cmd);

        if (stat(full, &st) == 0)
        {
            free(copy);
            return full;
        }
        free(full);
        token = strtok(NULL, ":");
    }
    free(copy);
    return NULL;
}
