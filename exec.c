#include "main.h"

void exec_command(char **argv)
{
    pid_t pid;
    char *full;

    if (!argv || !argv[0]) return;

    /* built-in: exit */
    if (strcmp(argv[0], "exit") == 0)
        exit(0);

    /* resolve path (do not fork if not found) */
    full = find_in_path(argv[0]);
    if (!full)
        return; /* silently ignore for 0.3; no fork if it doesn't exist */

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
        int status;
        waitpid(pid, &status, 0);
    }
    free(full);
}
