#include "main.h"

/**
	* read_input - Reads a line of input from stdin.
	* @input: Pointer to buffer to store input.
	* @len: Pointer to size of buffer.
	*
	* Return: Number of characters read or -1 on failure.
	*/
ssize_t read_input(char **input, size_t *len)
{
	return (getline(input, len, stdin));
}
