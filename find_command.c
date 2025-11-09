#include "main.h"

/**
 * find_command - finds the full path of a command
 * @cmd: the command to find
 * @envp: environment variables
 * Return: full path string (malloced) or NULL if not found
 */
char *find_command(char *cmd, char **envp)
{
    char *path_env, *path_dup, *dir;
    char *full_path;

    if (!cmd)
        return NULL;

    /* If command contains '/', treat it as absolute or relative path */
    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
        {
            full_path = malloc(strlen(cmd) + 1);
            if (!full_path)
                return NULL;
            strcpy(full_path, cmd);
            return full_path;
        }
        return NULL;
    }

    /* Get PATH from environment */
    path_env = get_path_env(envp);
    if (!path_env || path_env[0] == '\0') /* empty PATH */
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
        if (access(full_path, X_OK) == 0)
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
