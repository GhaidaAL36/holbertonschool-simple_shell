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
char **split_line(char *line);
void execute_command(char **args);
char *find_path(char *command);
void print_env(void);

#endif
