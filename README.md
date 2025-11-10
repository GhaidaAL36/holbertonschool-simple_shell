# Simple Shell - hsh

This project is a simple UNIX command interpreter written in C.
It replicates key functionalities of a traditional shell, including reading user input,
parsing commands, handling built-in commands, executing programs from PATH, and managing exit status.

The shell works in both interactive and non-interactive modes,
supports whitespace trimming, tokenization, PATH search, error formatting, and proper process handling.

---

### FEATURES
- Displays a prompt in interactive mode (:)).
- Reads input using getline.
- Trims leading and trailing spaces/tabs.
- Checks empty/whitespace-only commands.
- Tokenizes input into arguments.
- Handles built-in commands: exit, env.
- Resolves paths and executes external commands.
- Prints formatted error messages.
- Returns accurate exit status.

---

### HOW IT WORKS
1. Display prompt (interactive mode only).
2. Read input using getline().
3. Trim whitespace.
4. Check for empty lines.
5. Parse tokenized command.
6. Handle built-ins (exit, env).
7. Resolve command path.
8. Fork and execute.
9. Return exit status.

---

### COMPILATION
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

---

### USAGE

#### Interactive Mode:
./hsh
:) ls
:) pwd
:) exit

#### Non-interactive Mode:
echo "ls -l" | ./hsh

---

### FILE DESCRIPTION

main.c - Main loop, prompt, reading, trimming, parsing, execution flow
trim.c - Removes leading/trailing whitespace
isspace.c - Detects whitespace-only input
parse_command.c - Tokenizes command
handle_builtins.c - exit + env
handle_exit.c - exit implementation
handle_env.c - prints environment variables
get_path_env.c - returns PATH value
find_command.c - resolves commands via PATH
execute_command.c - fork + execve + wait
main.h - all prototypes

---

### EXAMPLES

:) ls
file1.c file2.c hsh

:) env
PATH=/usr/local/bin:/usr/bin:/bin

:) unknowncmd
./hsh: 1: unknowncmd: not found

---

### EXIT STATUS
- Returns exit status of last command.
- 127 if command not found.
