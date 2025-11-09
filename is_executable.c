#include "main.h"

/**
 * is_executable - checks if a file is executable
 * @path: path to the file
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}
