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

static void check_paths(struct s_data *input_data)
{
	int 	ret = 0;
	bool	bad_path = false;
	size_t	c = 0;
	struct stat *restrict data = (struct stat *restrict)malloc(sizeof(*data));
	if (!data)
		free_paths(input_data->paths, input_data->num_of_paths);

	ft_memset(data, 0, sizeof(data));
	for (; c < input_data->num_of_paths; c++) {
		ret = stat(input_data->paths[c], data);
		if (ret) {
			ft_printf("ft_ls: cannot access %s: No such file or directory\n", input_data->paths[c]);
			free(input_data->paths[c]);
			input_data->paths[c] = NULL;
			bad_path = true;
		}
	}
	free(data);
	if (bad_path) {
		for (c = 0; c < input_data->num_of_paths; c++) {
			if (input_data->paths[c])
				return ;
		}
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
	*data.paths = NULL;
	if (!data.paths)
		MALLOC_ERR_EXIT();
	counter = 0;
	for (int i = 1; i < argc; i++) {
		if (*argv[i] == '-') {
			data.options_set = true;
			for (size_t j = 1; argv[i][j]; j++) {
				set_option_value(&data, argv[i][j]);
			}
		} else {
			data.paths[counter++] = ft_strdup(argv[i]);
			if (!data.paths[counter - 1])
				free_paths(data.paths, data.num_of_paths);
		}
	}
	if (!counter) {
		data.paths[counter++] = ft_strdup(".");
		if (!data.paths[counter - 1])
			free_paths(data.paths, data.num_of_paths);
		data.paths[counter] = NULL;
	}
	return data;
}

int main(int argc, char **argv)
{
	t_data	input_data = parse_data(argc, argv);
	check_paths(&input_data);
	/*
	* Dynamic Memory Allocated: input_data->paths ** and *
	*/

	/*
	* At the time of the paths loop check if there is a null to skip it!
	*/

	return 0;
}