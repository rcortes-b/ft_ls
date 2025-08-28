#ifndef ERR_H
# define ERR_H

#include <unistd.h>
#include <stdlib.h>

#define MALLOC_ERR() \
    do { \
        write(2, "Memory allocation error\n", 24); \
        return NULL; \
    } while(0)

#define MALLOC_ERR_EXIT() \
    do { \
        write(2, "Memory allocation error\n", 24); \
        exit(1); \
    } while(0)

void free_paths_exit(char **paths, size_t amount);
void free_paths(char **paths, size_t amount);

#endif