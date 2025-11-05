#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char *read_line(void);
char **tokenize(char *line);
char *find_path(char *command);
void execute(char **args);
int _strcmp(char *s1, char *s2);
void free_args(char **args);

#endif
