#include "main.h"

/**
 * printEnv - Print all environment variables
 *
 * Return: Nothing
 */
void printEnv(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
