#include "main.h"

/**
 * handle_sigint - handles Ctrl+C signal (SIGINT)
 * @sig: signal number
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
