#include "main.h"

char *handle_path(char *input)
{
    char *path_env, *path_copy, *dir, *result;
    size_t len;

    if (!input)
        return (NULL);

    if (strchr(input, '/') != NULL)
        return (strdup(input));

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = strlen(dir) + 1 + strlen(input) + 1;
        result = malloc(len);
        if (!result)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(result, "%s/%s", dir, input);
        if (access(result, X_OK) == 0)
        {
            free(path_copy);
            return (result);
        }
        free(result);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}
