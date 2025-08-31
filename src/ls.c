#include "../inc/ls.h"
#include "../inc/entries.h"
#include "../inc/print.h"

/*
* -l, -R, -a, -r and -t
*/

static void free_data(struct s_list **lst)
{
	t_entries	*save_ent;
	t_list		*save_lst;
	while (*lst) {
		while ((*lst)->entries) {
			save_ent = (*lst)->entries;
			(*lst)->entries = (*lst)->entries->next;
			free(save_ent->name);
			free(save_ent->path);
			free(save_ent->stat_data);
			free(save_ent);
		}
		save_lst = *lst;
		*lst = (*lst)->next;
		free(save_lst->name);
		free(save_lst->root);
		free(save_lst);
	}
}

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
	t_list *lst, *tmp;
	t_data input_data;	
	input_data = parse_data(argc, argv);
	check_input(&input_data);

	lst = get_list(*input_data.paths, input_data.options);
	//if !lst
	iterate_dirs(&lst, input_data.options);
	free(*input_data.paths);
	for (size_t i = 1; i < input_data.num_of_paths; i++) {
		tmp = lst;
		if (input_data.paths[i]) {
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = get_list(input_data.paths[i], input_data.options);
			iterate_dirs(&tmp->next, input_data.options);
			free(input_data.paths[i]);
		}
	}
	free(input_data.paths);
	print_list(&lst, input_data.options, input_data.num_of_paths);
	free_data(&lst);
	/*
	* Dynamic Memory Allocated: input_data->paths ** and *
	*/

	/*
	* At the time of the paths loop check if there is a null to skip it!
	*/

	return 0;
}