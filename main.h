#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#include <signal.h> /* task 12 */
void handle_sigint(int sig); /* task 12 */

/* Prototypes */
int _isspace(char *s);
char *trim(char *str);
int is_executable(char *path);
char *get_path_env(char **envp);
char *find_command(char *cmd, char **envp);
char *try_cmd_path(char *dir, char *cmd);
char *cmd_with_slash(char *cmd);
int parse_command(char *line, char *args[]);
int handle_builtins(char *args[], char *line, char **envp, int *status);
int execute_command(char *args[], char **envp);

#endif /* MAIN_H */

