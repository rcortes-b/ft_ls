#ifndef ENTRIES_H
# define ENTRIES_H

#include "list.h"

t_entries *get_entries(DIR *root, char *root_path);
t_list *get_list(char *root);
void	iterate_dirs(t_list **lst);


#endif