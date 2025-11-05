#include "main.h"

void execute(char **argv)
{
    char *path;
    pid_t pid;

    if (!argv || !argv[0])
        return;

    if (strcmp(argv[0], "env") == 0)
    {
        print_env();
        return;
    }

    if (strchr(argv[0], '/'))
        path = argv[0];
    else
        path = handle_path(argv[0]);

    if (!path)
    {
        write(STDERR_FILENO, "not found\n", 10);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(path, argv, environ) == -1)
            perror("execve");
        exit(127);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);

    if (path != argv[0])
        free(path);
}
