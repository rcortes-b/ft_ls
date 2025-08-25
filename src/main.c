#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "utils.c"
#include <stdbool.h>
/*
* -l, -R, -a, -r and -t
*/
typedef struct s_options {
	bool	list;
	bool	recursive;
	bool	all;
	bool	reverse;
	bool	time;
}		t_options;

typedef struct s_data {
	t_options	options;
	char		*path;
}		t_data;

struct s_data parse_data(int argc, char **argv)
{
	t_data	data;

	if (argc == 1) {
		return data;
	} else {
		for (size_t i = 1; i < argc; i++) {
			if (*argv[i] == '-') {
				for (size_t j = 1; argv[i][j]; j++) {
					switch (argv[i][j]) {
						case 'l':
									data.options.list = true;
									break ;
						case 'r':
									data.options.reverse = true;
									break ;
						case 'R':
									data.options.recursive = true;
									break ;
						case 'a':
									data.options.all = true;
									break ;
						case 't':
									data.options.time = true;
									break ;
						default:
									write(2, "Invalid option.\n", 16);
									exit(1);
					}
				}
			} else {
				data.path = malloc(strlen(argv[i] + 1));
				size_t	l = 0;
				for (; argv[i][l]; l++)
					data.path[l] = argv[i][l];
				data.path[l] = '\0';
			}
		}
	}
	return data;
}

int main(int argc, char **argv)
{
	t_data	input_data = parse_data(argc, argv);
	struct stat *restrict data = malloc(sizeof(*data));
	memset(data, 0, sizeof(data));
	int ret = stat(input_data.path, data);
	if (ret) {
		write(2, "ft_ls: cannot access ", 21);
		write(2, input_data.path, strlen(input_data.path));
		write(2, ": No such file or directory\n", 28);
		exit(1);
	}
	printf("%d\n", data->st_mode);
	free(data);
	free(input_data.path);
	return ret;
}