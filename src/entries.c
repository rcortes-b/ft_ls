#include "../inc/entries.h"
#include "../inc/list.h"
#include "../inc/utils.h"
#include "../inc/sort.h"

t_entries *get_entries(DIR *root, char *root_path, t_options opt)
{
	struct dirent *entry;
	t_entries *entries = NULL;
	while ((entry = readdir(root)) != NULL) {
		if (!opt.all && *entry->d_name == '.')
			continue;
		if (!add_entry_back(&entries, get_new_entry(entry->d_name, ft_pathjoin(root_path, entry->d_name))))
			return NULL;
	}
	merge_sort(&entries, opt);
	return entries;
}

void iterate_dirs(t_list **lst, t_options opt)
{
	t_entries 	*aux;
	t_list		*last;

	if (!opt.recursive)
		return ;
	aux = (*lst)->entries;
	while (aux) {
		if (aux->stat_data && S_ISDIR(aux->stat_data->st_mode) && dir_is_valid(aux->path)) {
			last = *lst;
			while (last->next)
				last = last->next;
			last->next = get_list(aux->path, opt);
			/*
			* Free everything and NULL to keep freeing the head list;
			*/
			iterate_dirs(&last->next, opt);
		}
		aux = aux->next;
	}
	
}

t_list *get_list(char *root, t_options opt)
{
	t_list	*new_lst = (t_list*)malloc(sizeof(t_list));
	if (!new_lst)
		MALLOC_ERR();
	/*
	* Error check
	*/
	new_lst->name = ft_strdup(root);
	if (!new_lst->name) {
		free(new_lst);
		return NULL;
	}
	new_lst->root = opendir(root);
	if (!new_lst->root) {
		free(new_lst->name);
		free(new_lst);
		return NULL;
	}
	new_lst->next = NULL;
	new_lst->entries = get_entries(new_lst->root, root, opt);
	if (!new_lst->entries) {
		free(new_lst->name);
		free(new_lst->root);
		free(new_lst);
		return NULL;
	}
	return new_lst;
} 