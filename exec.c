#include "main.h"

void execute(char **argv)
{
    pid_t pid;
    char *path;
    int status;

    if (!argv || !argv[0])
        return;

    if (strcmp(argv[0], "exit") == 0)
        exit(0);

    path = find_path(argv[0]);
    if (!path)
        return;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(path);
        return;
    }

    if (pid == 0)
    {
        execve(path, argv, environ);
        perror(argv[0]);
        _exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(path);
}
