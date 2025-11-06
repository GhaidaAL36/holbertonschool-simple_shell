#include "main.h"

/* simple _getenv using environ (no getenv) */
char *_getenv_val(const char *name)
{
    size_t nlen;
    int i;

    if (!name || !*name) return NULL;
    nlen = strlen(name);

    for (i = 0; environ && environ[i]; i++)
    {
        if (!strncmp(environ[i], name, nlen) && environ[i][nlen] == '=')
            return environ[i] + nlen + 1; /* pointer to value inside environ */
    }
    return NULL;
}

int is_interactive(void)
{
    return isatty(STDIN_FILENO);
}

/* trim leading/trailing spaces and tabs/newlines (in place) */
void trim_ends(char *s)
{
    char *p, *end;

    if (!s) return;

    p = s;
    while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
        p++;
    if (p != s)
        memmove(s, p, strlen(p) + 1);

    if (!*s) return;

    end = s + strlen(s) - 1;
    while (end >= s && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';
}

int is_empty(const char *s)
{
    if (!s) return 1;
    while (*s)
    {
        if (*s != ' ' && *s != '\t' && *s != '\n')
            return 0;
        s++;
    }
    return 1;
}
