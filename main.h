#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

char *read_line(void);
char **get_argument(char *line);
void free_args(char **args);
void execute_command(char **args);
char *find_path(char *command);
void print_env(void);
int _strcmp(char *s1, char *s2);

#endif
