#include "main.h"

static void print_not_found(char *cmd)
{
    write(STDERR_FILENO, cmd, strlen(cmd));
    write(STDERR_FILENO, ": not found\n", 12);
}

void printEnv(void)
{
    char **env;

    for (env = environ; *env != NULL; env++)
    {
        write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
    }
}

void exec(char **args, char *input)
{
    pid_t childPid;
    int status;

    (void)input;

    if (access(args[0], X_OK) != 0)
    {
        print_not_found(args[0]);
        return;
    }

    childPid = fork();
    if (childPid == -1)
    {
        perror("fork");
        return;
    }
    else if (childPid == 0)
    {
        execve(args[0], args, environ);
        perror("execve");
        _exit(127);
    }
    else
    {
        waitpid(childPid, &status, 0);
    }
}

void tokenize(char *input, char *args[])
{
    char *token;
    size_t i = 0;
    char *full = NULL;

    for (i = 0; i < 64; i++)
        args[i] = NULL;
    i = 0;

    token = strtok(input, " \t");
    while (token)
    {
        args[i++] = token;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    if (args[0] == NULL)
        return;

    if (strcmp(args[0], "env") == 0)
    {
        printEnv();
        return;
    }

    if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
        exit(0);

    full = handle_path(args[0]);
    if (full)
    {
        char *old0 = args[0];
        args[0] = full;
        exec(args, input);
        free(args[0]);
        args[0] = old0;
    }
    else
    {
        print_not_found(args[0]);
    }
}
