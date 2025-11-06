#include "main.h"

int main(void)
{
    char *input = NULL;
    char *args[64] = { NULL };
    size_t inputSize = 0;
    ssize_t inputRead;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        inputRead = getline(&input, &inputSize, stdin);
        if (inputRead == EOF)
        {
            free(input);
            return (0);
        }

        if (inputRead > 0 && input[inputRead - 1] == '\n')
            input[inputRead - 1] = '\0';

        {
            char *p = input;
            while (*p == ' ' || *p == '\t')
                p++;
            if (*p == '\0')
                continue;
        }

        tokenize(input, args);
    }

    free(input);
    return (0);
}
