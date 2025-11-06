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
    if (pid == 0)
    {
        execve(path, args, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    else
        perror("fork");

    free(path);
}
