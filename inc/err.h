#ifndef ERR_H
# define ERR_H

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

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

struct s_list;

void free_paths_exit(char **paths, size_t amount);
void free_paths(char **paths, size_t amount);
void free_data(struct s_list **lst);

#define FREE_AND_EXIT(lst, paths, amount) \
    do { \
        ft_printf("%s\n", strerror(errno)); \
		free_paths(paths, amount); \
		free_data(lst); \
        exit(1); \
    } while(0)

#endif