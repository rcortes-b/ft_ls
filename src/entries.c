#include "../inc/entries.h"
#include "../inc/list.h"
#include "../inc/utils.h"

t_entries *get_entries(DIR *root, char *root_path)
{
	struct dirent *entry;
	t_entries *entries = NULL;
	while ((entry = readdir(root)) != NULL) {
		ft_printf("cmon %s\n", ft_pathjoin(root_path, entry->d_name));
		add_entry_back(&entries, get_new_entry(entry->d_name, ft_pathjoin(root_path, entry->d_name), get_last_entry(entries)));
	}
	return entries;
}

void	iterate_dirs(t_list **lst)
{
	t_list	*tmp_list;
	t_list	*aux;

	tmp_list = *lst;
	aux = *lst;
	while (tmp_list) {
		ft_printf("TMP_LIST: %s\n", tmp_list->name);
		t_entries *tmp_entries = tmp_list->entries;
		while (tmp_entries) {
			ft_printf("TMP_ENTRIES: %s\n", tmp_entries->path);
			if (tmp_entries->stat_data && S_ISDIR(tmp_entries->stat_data->st_mode) && dir_is_valid(tmp_entries->path)) {
				ft_printf("tmp_entries_path: %s\n", tmp_entries->path);
				tmp_list->next = get_list(tmp_entries->name);
				tmp_list = tmp_list->next;
			}
			tmp_entries = tmp_entries->next;
		}
		aux = aux->next;
		tmp_list = aux;
	}
}

t_list *get_list(char *root)
{
	t_list	*new_lst = (t_list*)malloc(sizeof(new_lst));
	if (!new_lst)
		MALLOC_ERR();
	/*
	* Error check
	*/
	new_lst->name = ft_strdup(root);
	new_lst->root = opendir(root);
	if (!new_lst->root) {
		strerror(errno);
		return NULL;
	}
	new_lst->next = NULL;
	new_lst->entries = get_entries(new_lst->root, root);
	/*while (new_lst->entries) {
		ft_printf("%s ", new_lst->entries->name);
		if (new_lst->entries->prev)
			ft_printf("%s\n", new_lst->entries->prev->name);
		else
			ft_printf("\n");
		new_lst->entries = new_lst->entries->next;
	}
	ft_printf("\n");*/
	return new_lst;
} 