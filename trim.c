#include "main.h"
#include <string.h>

char *trim(char *str)
{
    char *end;

    if (!str)
	    return (NULL);

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        *end-- = '\0';

    return str;
}
