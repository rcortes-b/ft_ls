#include "../inc/ls.h"

/*
* -l, -R, -a, -r and -t
*/

static void init_data(struct s_data *data)
{
	data->options.all = false;
	data->options.list = false;
	data->options.recursive = false;
	data->options.reverse = false;
	data->options.time = false;
	data->options_set = false;
	data->paths = NULL;
	data->num_of_paths = 0;
}

static size_t num_of_paths(int argc, char **argv)
{
	size_t counter = 0;
	for (int i = 1; i < argc; i++)
		if (*argv[i] != '-')
			counter++;
	if (!counter)
		counter = 1;
	return counter;
}

static void check_paths(t_data *input_data)
{
	struct stat *restrict data = malloc(sizeof(*data));
	int 	ret = 0;
	bool	bad_path = false;
	size_t	c = 0;

	ft_memset(data, 0, sizeof(data));
	for (; c < input_data->num_of_paths; c++) {
		ret = stat(input_data->paths[c], data);
		if (ret) {
			ft_printf("ft_ls: cannot access %s: No such file or directory\n", input_data->paths[c]);
			bad_path = true;
		}
	}
	free(data);
	if (bad_path) {
		for (c = 0; c < input_data->num_of_paths; c++)
			free(input_data->paths[c]);
		free(input_data->paths);
		exit(1);
	}
}

struct s_data parse_data(int argc, char **argv)
{
	t_data	data;
	init_data(&data);
	size_t counter = num_of_paths(argc, argv);
	data.num_of_paths = counter;
	data.paths = (char**)malloc(sizeof(char*) * (counter + 1));
	counter = 0;
	for (int i = 1; i < argc; i++) {
		if (*argv[i] == '-') {
			data.options_set = true;
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
			data.paths[counter++] = ft_strdup(argv[i]);
		}
	}
	if (!counter) {
		data.paths[counter++] = ft_strdup(".");
		data.paths[counter] = NULL;
	}
	return data;
}

int main(int argc, char **argv)
{
	t_data	input_data = parse_data(argc, argv);
	check_paths(&input_data);
	DIR* root = opendir(input_data.paths[0]);
	struct dirent *loppdir;
	while ((loppdir = readdir(root)) != NULL) {
		ft_printf("%s ", loppdir->d_name);
	}
	ft_printf("\n");
	
	/*
	* La prioridad de orden es -a/-R, luego -t y luego -r (primero saca todos los files, ordena por tiempo y luego lo pone al reves)
	*/

	return 0;
}