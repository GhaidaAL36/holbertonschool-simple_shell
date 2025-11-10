# Simple Shell - hsh

This project is a simple UNIX command interpreter written in C.
It mimics a small subset of the functionalities of a standard shell.
The shell reads user input, parses commands, executes built-in commands,
searches for executables inside the PATH, and runs external programs.

### Features
- Displays a prompt in interactive mode.
- Reads and parses user input.
- Trims leading and trailing whitespace.
- Tokenizes the input into arguments.
- Handles built-in commands: exit, env.
- Searches for commands in the PATH.
- Executes external commands using fork and execve.
- Prints errors in the correct shell format.
- Returns proper exit status codes.

### Compilation
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

### Usage
Interactive mode:
./hsh
:) ls
:) pwd
:) exit

### Non-interactive mode:
echo "ls -l" | ./hsh

### File Description
main.c - Entry point of the shell.
trim.c - Removes leading/trailing whitespace.
isspace.c - Checks if a string contains only whitespace.
parse_command.c - Tokenizes the input.
handle_builtins.c - Built-in commands.
handle_exit.c - Exit command.
handle_env.c - Env command.
get_path_env.c - Gets PATH.
find_command.c - Finds command inside PATH.
execute_command.c - Executes external commands.
main.h - Prototypes.

### Examples
:) ls
file1.c file2.c hsh

:) env
PATH=/usr/bin:/bin

:) unknowncmd
./hsh: 1: unknowncmd: not found

### Exit Status
- Returns exit status of last command.
- Returns 127 if command not found.

### Authors
Lina

