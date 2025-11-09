#include "main.h"

/**
 * main - simple UNIX command line interpreter
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 * Return: 0 on success
 */
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
            i = 0;
            token = strtok(command, " \t\n");
            while (token != NULL && i < 99)
            {
                args[i++] = token;
                token = strtok(NULL, " \t\n");
            }
            args[i] = NULL;

            /* Find command in PATH */
            path_cmd = find_command(args[0], envp);
            if (!path_cmd)
            {
                fprintf(stderr, "%s: command not found\n", args[0]);
                continue; /* do NOT fork if command does not exist */
            }

            pid = fork();
            if (pid == -1)
            {
                perror(argv[0]);
                free(path_cmd);
                continue;
            }
            else if (pid == 0)
            {
                execve(path_cmd, args, envp);
                perror(argv[0]);
                free(path_cmd);
                exit(EXIT_FAILURE);
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

