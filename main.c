#include "main.h"

/**
 * get_path_from_env - retrieves the PATH from envp
 * @envp: environment variables
 * Return: pointer to PATH string or NULL if not found
 */
char *get_path_from_env(char **envp)
{
    int i = 0;

    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return envp[i] + 5; /* skip "PATH=" */
        i++;
    }
    return NULL;
}

/**
 * find_command - finds executable path for a command
 * @cmd: command name
 * @envp: environment variables
 * Return: full path string (malloc) or NULL
 */
char *find_command(char *cmd, char **envp)
{
    char *path_env = get_path_from_env(envp);
    char *path_dup, *dir;
    char *full_path = NULL;

    if (!path_env || !cmd)
        return NULL;

    if (strchr(cmd, '/')) /* absolute or relative path */
    {
        if (access(cmd, X_OK) == 0)
            return strdup(cmd);
        return NULL;
    }

    path_dup = strdup(path_env);
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
        if (access(full_path, X_OK) == 0)
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
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    char *command;
    char *path_cmd;

    (void)argc;

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
            int i = 0;
            char *token = strtok(command, " \t\n");

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

