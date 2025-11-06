#include "main.h"

/* Find command in PATH, return malloc'd full path */
char *find_in_path(const char *cmd)
{
    char *path, *dup, *dir, *full;
    size_t cmdlen, dlen;

    if (!cmd || !*cmd)
        return (NULL);

    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (strdup(cmd));
        return (NULL);
    }

    path = _getenv_val("PATH");
    if (!path || !*path)
        return (NULL);

    dup = strdup(path);
    if (!dup)
        return (NULL);

    cmdlen = strlen(cmd);
    dir = strtok(dup, ":");
    while (dir)
    {
        dlen = strlen(dir);
        full = malloc(dlen + cmdlen + 2);
        if (!full)
        {
            free(dup);
            return (NULL);
        }
        memcpy(full, dir, dlen);
        full[dlen] = '/';
        memcpy(full + dlen + 1, cmd, cmdlen);
        full[dlen + 1 + cmdlen] = '\0';

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
