#include "../inc/list.h"

t_entries *get_new_entry(char *name, char *path)
{
	if (!path)
		return NULL;
	t_entries *entries = (t_entries *)malloc(sizeof(t_entries));
	if (!entries) {
		free(path);
		MALLOC_ERR();
	}
	entries->name = ft_strdup(name);
	if (!entries->name) {
		free(path);
		free(entries);
		return NULL;
	}
	entries->path = path;
	entries->next = NULL;
	entries->stat_data = (struct stat *)malloc(sizeof(struct stat));
	if (!entries->stat_data) {
		free(path);
		free(entries);
		free(entries->name);
		return NULL;
	}
	int ret = stat(entries->path, entries->stat_data);
	if (ret < 0) {
		free(path);
		free(entries);
		free(entries->name);
		free(entries->stat_data);
		entries->stat_data = NULL;
		return NULL;
	}
	return entries;
}

t_entries *get_last_entry(t_entries *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list *get_last_list(t_list *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_entries	*add_entry_back(t_entries **lst, t_entries *new)
{
	t_entries	*tmp;

	if (!new)
		return NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return new;
	}
	tmp = *lst;
	tmp = get_last_entry(tmp);
	tmp->next = new;
	return new;
}