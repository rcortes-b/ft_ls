#ifndef ENTRIES_H
# define ENTRIES_H

#include "list.h"

t_entries *get_new_entry(char *name, t_entries *last);
t_entries *get_last_entry(t_entries *lst);
void	add_entry_back(t_entries **lst, t_entries *new);
t_entries *get_entries(DIR *root);
t_list *get_list(char *root);

#endif