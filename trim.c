#include "main.h"

char *trim(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t')
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        *end-- = '\0';

    return str;
}
