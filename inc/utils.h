#ifndef UTILS_H
# define UTILS_H

#include "ls.h"

void	set_option_value(t_data *data, char c);
size_t	num_of_paths(int argc, char **argv);
bool	dir_is_valid(char *path);
int		ft_strcmp(char *s1, char *s2);
size_t	number_len(int value);

#endif