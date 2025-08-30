#include "../inc/utils.h"

bool	dir_is_valid(char *path)
{
	if ((!ft_strncmp("..", &path[ft_strlen(path) - 2], 2)) ||
			(!ft_strncmp(".", &path[ft_strlen(path) - 1], 1)))
			return false;
	return true;
}

void	set_option_value(struct s_data *data, char c)
{
	switch (c) {
		case 'l':
					data->options.list = true;
						break ;
		case 'r':
					data->options.reverse = true;
					break ;
		case 'R':
					data->options.recursive = true;
					break ;
		case 'a':
					data->options.all = true;
					break ;
		case 't':
					data->options.time = true;
					break ;
		default:
					write(2, "Invalid option.\n", 16);
					free_paths_exit(data->paths, data->num_of_paths);
	}
}

size_t num_of_paths(int argc, char **argv)
{
	size_t counter = 0;
	for (int i = 1; i < argc; i++)
		if (*argv[i] != '-')
			counter++;
	if (!counter)
		counter = 1;
	return counter;
}


int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
