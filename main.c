#include "main.h"

int main(int argc, char **argv, char **envp)
{
    char *line;
    size_t len;
    ssize_t nread;
    pid_t pid;
    int status;
    char *command;
    char *path_cmd;
    char *args[100];
    int i;
    char *token;

    (void)argc;
    (void)argv;

    line = NULL;
    len = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        command = trim(line);

        if (!_isspace(command))
        {
            /* tokenize command */
            i = 0;
            token = strtok(command, " \t\n");
            while (token != NULL && i < 99)
            {
                args[i++] = token;
                token = strtok(NULL, " \t\n");
            }
            args[i] = NULL;

            path_cmd = find_command(args[0], envp);
            if (!path_cmd)
            {
                write(STDERR_FILENO, args[0], strlen(args[0]));
                write(STDERR_FILENO, ": command not found\n", 20);
                continue;
            }

            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                free(path_cmd);
                continue;
            }
            else if (pid == 0)
            {
                execve(path_cmd, args, envp);
                perror("execve");
                _exit(EXIT_FAILURE);
            }
            else
            {
                wait(&status);
                free(path_cmd);
            }
        }
    }

    free(line);
    return 0;
}

