#include "main.h"

void exec_command(char **argv)
{
    pid_t pid;
    char *full;
    int status;

    if (!argv || !argv[0])
        return;

    /* handle built-in exit */
    if (strcmp(argv[0], "exit") == 0)
        exit(0);

    /* find in PATH */
    full = find_in_path(argv[0]);

    if (!full)
    {
        /* print error if not found */
        fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
        return;
    }

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
        perror(argv[0]);
        _exit(126);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(full);
}
