#include "main.h"

/**
	* get_path_env - retrieves the value of the PATH environment variable
	* @envp: array of environment variables
	*
	* Return: pointer to the PATH string (skipping "PATH=") if found,
	*         NULL otherwise
	*/
char *get_path_env(char **envp)
{
	int i = 0;

	if (!envp)
	return (NULL);

	while (envp[i])
	{
	if (strncmp(envp[i], "PATH=", 5) == 0)
	return (envp[i] + 5);
	i++;
	}
	return (NULL);
}
