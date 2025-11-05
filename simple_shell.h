#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_prompt(void);
ssize_t read_input(char **input, size_t *len);
void execute_command(char *command, char *program_name);
char *trim_whitespace(char *str);
int main(int argc __attribute__((unused)), char *argv[]);


#endif
