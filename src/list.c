#include "../inc/list.h"

t_entries *get_new_entry(char *name, char *path)
{
	t_entries *entries = (t_entries *)malloc(sizeof(t_entries));
	if (!entries)
		MALLOC_ERR();
	entries->name = ft_strdup(name);
	//ft_printf("PATH %s\n", path);
	entries->path = path;
	entries->next = NULL;
	entries->stat_data = (struct stat *)malloc(sizeof(struct stat));

	int ret = stat(entries->path, entries->stat_data);
	if (ret < 0) {
	//	ft_printf("edfs %s\n", entries->name);
		/*
		* Review this error
		*/
	//write(2, "Stat error\n", 11);
		entries->stat_data = NULL;
	} else {
	//	ft_printf("%s\n", entries->name);
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

void	add_entry_back(t_entries **lst, t_entries *new)
{
	t_entries	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp = get_last_entry(tmp);
	tmp->next = new;
}