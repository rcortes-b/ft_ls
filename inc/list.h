#ifndef LIST_H
# define LIST_H

#include "ls.h"
#include <sys/stat.h>

typedef struct s_entries {
	char					*path;
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

t_entries *get_new_entry(char *name, char *path, t_entries *last);
t_entries	*get_last_entry(t_entries *lst);
void		add_entry_back(t_entries **lst, t_entries *new);

 #endif