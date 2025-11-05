#include "simple_shell.h"

/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
