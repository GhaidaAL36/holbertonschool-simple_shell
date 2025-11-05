#include "simple_shell.h"

/**
 * execute_command - executes a command
 * @args: array of arguments
 * @env: environment variables
 */
void execute_command(char **args, char **env)
{
	char *command = args[0];
	char *path_env, *path_copy, *token, full_path[1024];
	struct stat st;

	/* If command contains '/' (absolute or relative path) */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
		{
			execve(command, args, env);
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "./hsh: %s: not found\n", command);
			return;
		}
	}

	/* Handle empty or missing PATH */
	path_env = getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
	{
		fprintf(stderr, "./hsh: %s: not found\n", command);
		return;
	}

	path_copy = strdup(path_env);
	token = strtok(path_copy, ":");
	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			execve(full_path, args, env);
			perror("./hsh");
			free(path_copy);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "./hsh: %s: not found\n", command);
	free(path_copy);
}
