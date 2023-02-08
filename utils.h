#include <stdlib.h>
#include <stdio.h>

#define ASSERT(x)                              \
    do                                         \
    {                                          \
        if (!(x))                              \
        {                                      \
            perror("assertion " #x " failed"); \
            exit(EXIT_FAILURE);                \
        }                                      \
    } while (0);
