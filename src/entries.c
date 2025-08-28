#include "../inc/entries.h"
#include "../inc/list.h"

t_entries *get_entries(DIR *root)
{
	struct dirent *entry;
	t_entries *entries = NULL;
	while ((entry = readdir(root)) != NULL) {
		add_entry_back(&entries, get_new_entry(entry->d_name, get_last_entry(entries)));
	}
	return entries;
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
	new_lst->entries = get_entries(new_lst->root);
	while (new_lst->entries) {
		ft_printf("%s ", new_lst->entries->name);
		new_lst->entries = new_lst->entries->next;
	}
	ft_printf("\n");
	return new_lst;
} 