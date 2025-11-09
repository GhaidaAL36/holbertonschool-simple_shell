#include "main.h"

int is_executable(char *path)
{
    return (access(path, X_OK) == 0);
}
