#include "../inc/err.h"

void free_paths_exit(char **paths, size_t amount)
{
	size_t i = 0;
	while (i < amount) {
		if (paths[i])
			free(paths[i]);
		else
			break;
		i++;
	}
	free(paths);
	exit(1);
}

void free_paths(char **paths, size_t amount)
{
	size_t i = 0;
	while (i < amount) {
		if (paths[i])
			free(paths[i]);
		else
			break;
		i++;
	}
	free(paths);
}

void free_data(struct s_list **lst)
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
