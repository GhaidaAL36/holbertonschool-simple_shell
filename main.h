#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

char **tokenize(char *line);
char *get_env_path(void);
char *find_command(char *cmd);
void execute(char **argv);

#endif
