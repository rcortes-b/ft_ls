#ifndef PRINT_H
#define PRINT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "list.h"
#include "ls.h"

#define WIDTH 180

void	print_list(struct s_list **list, t_options opt, size_t amount);

#endif