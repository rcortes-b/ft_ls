#ifndef LS_H
# define LS_H

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

typedef struct s_options {
	bool	list;
	bool	recursive;
	bool	all;
	bool	reverse;
	bool	time;
}		t_options;

typedef struct s_data {
	t_options	options;
	bool		options_set;
	char		**paths;
	size_t		num_of_paths;
}		t_data;

#endif