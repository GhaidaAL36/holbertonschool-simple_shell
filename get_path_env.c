#include "main.h"

char *get_path_env(char **envp)
{
    int i = 0;

    if (!envp)
        return NULL;

    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return envp[i] + 5; /* skip "PATH=" */
        i++;
    }
    return NULL;
}
