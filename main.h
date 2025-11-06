#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int execute(char *const command[], char **envp);
char *_getenv(const char *name);
char **pathfinder(char *cmd, char **command);
void parse(char command[], char **envp);
int print_env(void);

#endif /* SIMPLE_SHELL */
