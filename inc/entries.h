#ifndef ENTRIES_H
# define ENTRIES_H

#include "list.h"

t_entries *get_entries(DIR *root, char *root_path, t_options opt);
t_list *get_list(char *root, t_options opt);
void	iterate_dirs(t_list **lst, t_options opt);

#endif