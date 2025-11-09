#include "main.h"

char *find_command(char *cmd, char **envp)
{
    char *path_env, *path_dup, *dir;
    char *full_path;

    if (!cmd)
        return NULL;

    if (strchr(cmd, '/')) /* absolute or relative path */
    {
        if (is_executable(cmd))
        {
            full_path = malloc(strlen(cmd) + 1);
            if (full_path)
                strcpy(full_path, cmd);
            return full_path;
        }
        return NULL;
    }

    path_env = get_path_env(envp);
    if (!path_env)
        return NULL;

    path_dup = malloc(strlen(path_env) + 1);
    if (!path_dup)
        return NULL;
    strcpy(path_dup, path_env);

    dir = strtok(path_dup, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
        {
            free(path_dup);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, cmd);
        if (is_executable(full_path))
        {
            free(path_dup);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_dup);
    return NULL;
}
