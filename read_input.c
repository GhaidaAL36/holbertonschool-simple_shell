/**
 * split_line - split input string into tokens
 * @line: input string
 * Return: array of arguments (must be freed by caller)
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens;
	char *token;

	if (!line)
		return (NULL);

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = token;
		if (i >= bufsize - 1)
		{
			bufsize *= 2;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}
