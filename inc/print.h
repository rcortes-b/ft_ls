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

struct s_options;
typedef struct s_list t_list;

typedef struct s_padding {
	size_t	nlink;
	size_t	pwusize;
	size_t	grpsize;
	size_t	filesize;
}	t_padding;

void	print_list(struct s_list **list, struct s_options opt, size_t amount);

#endif