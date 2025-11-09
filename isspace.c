#include "main.h"
int _isspace(char *str)
{
    int i = 0;

    if (!str)
        return 1; /* consider NULL as whitespace */

    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return 0; /* found a non-space character */
        i++;
    }
    return 1; /* only spaces/tabs/newlines */
}
