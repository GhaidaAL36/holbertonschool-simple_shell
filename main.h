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
char **tokenize(char *line);
void execute(char **argv);
char *handle_path(char *cmd);
void print_env(void);

#endif
