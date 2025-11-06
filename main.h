#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char **tokenize(char *line);
char *find_path(char *command);
void execute(char **args);
void free_tokens(char **tokens);

#endif
