#include "main.h"

/**
 * execute - run a command
 * @args: argument list
 */
void execute(char **args)
{
    pid_t pid;
    char *path;

    if (!args || !args[0])
        return;

    path = find_path(args[0]);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(path);
        return;
    }

    if (pid == 0)
    {
        if (execve(path, args, environ) == -1)
            perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }

    free(path);
}
