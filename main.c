#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * is_executable - check if a file is executable
 * @path: path to file
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(char *path)
{
    return (access(path, X_OK) == 0);
}

/**
 * strdup_c90 - duplicate a string (C90 safe)
 * @s: string to duplicate
 * Return: pointer to duplicated string
 */
char *strdup_c90(const char *s)
{
    char *dup = malloc(strlen(s) + 1);
    if (dup)
        strcpy(dup, s);
    return dup;
}

/**
 * find_command - find full path of command using PATH
 * @cmd: command
 * Return: malloced full path, or NULL if not found
 */
char *find_command(char *cmd)
{
    char *path_env;
    char *path_dup;
    char *dir;
    char *full_path;

    if (!cmd)
        return NULL;

    if (strchr(cmd, '/')) /* absolute or relative path */
    {
        if (is_executable(cmd))
            return strdup_c90(cmd);
        return NULL;
    }

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    path_dup = strdup_c90(path_env);
    if (!path_dup)
        return NULL;

    dir = strtok(path_dup, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path)
        {
            free(path_dup);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, cmd);
        if (is_executable(full_path))
        {
            free(path_dup);
            return full_path;
        }
        free(full_path);
        full_path = NULL;
        dir = strtok(NULL, ":");
    }

    free(path_dup);
    return NULL;
}

/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 * Return: 0
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
            char *args[100];
            int i;
            char *token;

            i = 0;
            token = strtok(command, " \t\n");
            while (token && i < 99)
            {
                args[i++] = token;
                token = strtok(NULL, " \t\n");
            }
            args[i] = NULL;

            path_cmd = find_command(args[0]);
            if (!path_cmd)
            {
                fprintf(stderr, "%s: command not found\n", args[0]);
                continue;
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
                perror(args[0]);
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
