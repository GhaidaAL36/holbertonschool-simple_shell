#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Prototypes */
int _isspace(char *s);
char *trim(char *str);
int is_executable(char *path);
char *get_path_env(char **envp);
char *find_command(char *cmd, char **envp);

#endif /* MAIN_H */

