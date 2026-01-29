#include "../inc/ls.h"
#include "../inc/entries.h"
#include "../inc/print.h"
#include "../inc/err.h"

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

static void check_input(struct s_data *input_data)
{
	int 	ret = 0;
	bool	bad_path = false;
	size_t	c = 0;
	struct stat *restrict data;

	data = (struct stat *restrict)malloc(sizeof(*data));
	if (!data)
		free_paths_exit(input_data->paths, input_data->num_of_paths);
	ft_memset(data, 0, sizeof(data));

	while (c < input_data->num_of_paths)
	{
		ret = stat(input_data->paths[c], data);
		if (ret) {
			ft_printf("ft_ls: cannot access '%s': No such file or directory\n", input_data->paths[c]);
			free(input_data->paths[c]);
			input_data->paths[c] = NULL;
			bad_path = true;
		}
		c++;
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
	size_t counter;

	init_data(&data);
	counter = num_of_paths(argc, argv);
	data.num_of_paths = counter;
	data.paths = (char**)malloc(sizeof(char*) * (counter + 1));
	if (!data.paths)
		MALLOC_ERR_EXIT();
	*data.paths = NULL;
	counter = 0;
	for (int i = 1; i < argc; i++) {
		if (ft_strlen(argv[i]) > 1 && *argv[i] == '-') {
			data.options_set = true;
			for (size_t j = 1; argv[i][j]; j++) {
				set_option_value(&data, argv[i][j]);
			}
		} else {
			data.paths[counter++] = ft_strdup(argv[i]);
			if (!data.paths[counter - 1])
				free_paths_exit(data.paths, data.num_of_paths);
		}
	}
	if (!counter) {
		data.paths[counter++] = ft_strdup(".");
		if (!data.paths[counter - 1])
			free_paths_exit(data.paths, data.num_of_paths);
		data.paths[counter] = NULL;
	}
	return data;
}

int main(int argc, char **argv)
{
	t_list *lst, *tmp, *value;
	t_data input_data;	

	input_data = parse_data(argc, argv);
	check_input(&input_data);

	lst = NULL;
	for (size_t i = 0; i < input_data.num_of_paths; i++) {
		if (input_data.paths[i]) {
			tmp = get_last_list(lst);
			value = get_list(input_data.paths[i], input_data.options);
			if (!value)
				FREE_AND_EXIT(&lst, input_data.paths, input_data.num_of_paths);
			if (!lst)
				lst = value;
			else
				tmp->next = value;
			if (!iterate_dirs(&value, input_data.options))
				FREE_AND_EXIT(&lst, input_data.paths, input_data.num_of_paths);
			free(input_data.paths[i]);
			input_data.paths[i] = NULL;
		}
	}
	free(input_data.paths);
	print_list(&lst, input_data.options, input_data.num_of_paths);
	free_data(&lst);

	return 0;
}