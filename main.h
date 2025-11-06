#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/* utils */
char *_getenv_val(const char *name);
int   is_interactive(void);
void  trim_ends(char *s);
int   is_empty(const char *s);

/* tokenizer */
char **tokenize(const char *line);

/* path */
char *find_in_path(const char *cmd);

/* exec */
void  exec_command(char **argv);

#endif /* MAIN_H */
