#include "../inc/print.h"

static blkcnt_t get_total_block_size(t_entries *entries)
{
	blkcnt_t counter = 0;
	while (entries) {
		counter += entries->stat_data->st_blocks;
		entries = entries->next;
	}
	return counter;
}

static void	print_entry_as_list(t_entries *entry)
{
	(void)entry;
}

void	print_list(struct s_list *lst, t_options opt, size_t amount)
{
	while (lst) {
		if (opt.recursive || amount > 1)
			ft_printf("%s:\n", lst->name);
		if (opt.list)
			ft_printf("total %d\n", get_total_block_size(lst->entries) / 2);
		while (lst->entries) {
			if (!opt.list)
				ft_printf("%s ", lst->entries->name);
			else
				print_entry_as_list(lst->entries);
			lst->entries = lst->entries->next;
		}
		ft_printf("\n");
		if (opt.recursive || amount > 1)
			ft_printf("\n");
		lst = lst->next;
	}
}
