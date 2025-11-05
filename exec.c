#include "main.h"

/**
 * execute - create child and run command
 */
void execute(char **args)
{
    pid_t pid;
    char *cmd_path;
    struct stat st;

    if (stat(args[0], &st) == 0)
        cmd_path = args[0];
    else
        cmd_path = find_path(args[0]);

    if (!cmd_path)
    {
        perror(args[0]);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
            perror("execve");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);

    if (cmd_path != args[0])
        free(cmd_path);
}
