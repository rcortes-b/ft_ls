#ifndef LIST_H
# define LIST_H

#include "ls.h"
#include <sys/stat.h>

typedef struct s_entries {
	char					*name;
	struct stat *restrict	stat_data;
	struct s_entries		*prev;
	struct s_entries		*next;
}	t_entries;

typedef struct s_list {
	char			*name;
	DIR				*root;
	t_entries		*entries;
	struct s_list	*next;
}	t_list;

 #endif