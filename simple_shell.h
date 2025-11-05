#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

char **parse_line(char *line);
void execute_command(char **args, char **env);
void print_prompt(void);
char *read_input(void);
void trim_whitespace(char *str);

#endif
