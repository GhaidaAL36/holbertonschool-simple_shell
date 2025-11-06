#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int execute(char **command, char **envp);
char *_getenv(const char *name);
char **pathfinder(char *cmd, char **command);
void parse(char *command, char **envp);
int print_env(void);

#endif /* MAIN_H */
