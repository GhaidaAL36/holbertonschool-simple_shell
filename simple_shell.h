#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_prompt(void);
ssize_t read_input(char **input, size_t *len);        /* getline-style */
char *trim_whitespace(char *str);
void execute_command(char *command, char *program_name);

extern char **environ;

#endif /* SIMPLE_SHELL_H */
