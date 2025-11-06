int execute(char *const command[], char **envp)
{
	pid_t pid;
	int status;
	char **temp;
	char *to_free = NULL;

	(void) envp;
	temp = pathfinder(command[0], (char **) command);
	if (!temp)
	{
		write(STDERR_FILENO, command[0], strlen(command[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127);
	}

	/* إذا كان تم عمل malloc لمسار جديد */
	if (temp[0] != command[0])
		to_free = temp[0];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (to_free)
			free(to_free);
		return (1);
	}
	if (pid == 0)
	{
		execve(temp[0], (char *const *)command, environ);
		perror(command[0]);
		if (to_free)
			free(to_free);
		_exit(2);
	}
	else
		waitpid(pid, &status, 0);

	if (to_free)
		free(to_free);
	return (0);
}
