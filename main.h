#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Function prototypes */
void exec(char **args, char *input);
void tokenize(char *input, char *args[]);
void printEnv(void);
char *handle_path(char *input);

#endif /* MAIN_H */
