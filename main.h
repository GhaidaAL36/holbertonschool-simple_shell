#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
	* print_prompt - prints the shell prompt
	*/
void print_prompt(void);

/**
	* read_input - reads a line from standard input
	* @input: pointer to store the input string
	* @len: pointer to the size of the string
	*
	* Return: number of characters read, or -1 on failure
	*/
ssize_t read_input(char **input, size_t *len);

/**
	* trim_whitespace - removes leading and trailing whitespace
	* @str: string to trim
	*
	* Return: pointer to the trimmed string
	*/
char *trim_whitespace(char *str);

/**
	* split_args - splits a command string into arguments
	* @command: command string
	* @args: array to store arguments
	*/
void split_args(char *command, char **args);

/**
	* resolve_path - resolves the full path of a command
	* @args: command arguments
	* @program_name: name of the program
	*
	* Return: 0 on success, -1 on failure
	*/
int resolve_path(char **args, char *program_name);

/**
	* execute_command - executes a command
	* @command: command string
	* @program_name: name of the shell program
	*/
void execute_command(char *command, char *program_name);
char *_strdup(const char *s);

#endif /* MAIN_H */

