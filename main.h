#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void print_prompt(void);
ssize_t read_input(char **input, size_t *len);
char *trim_whitespace(char *str);
void split_args(char *command, char **args);
int resolve_path(char **args, char *program_name);
void execute_command(char *command, char *program_name);

#endif /* MAIN_H */
