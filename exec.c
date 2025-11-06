#include "main.h"

void exec_command(char **argv)
{
    pid_t pid;
    char *full;
    int status;

    if (!argv || !argv[0])
        return;

    if (strcmp(argv[0], "exit") == 0)
        exit(0);

    full = find_in_path(argv[0]);
    if (!full)
        return; /* PATH not found → don't fork */

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(full);
        return;
    }

    if (pid == 0)
    {
        execve(full, argv, environ);
        perror("execve");
        _exit(126);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(full);
}
