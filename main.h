#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

void execute(char **argv);
void print_env(void);
char *find_in_path(const char *cmd);
char *read_line(void);
char **split_line(char *line);

#endif
