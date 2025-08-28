#include "../inc/list.h"

t_entries *get_new_entry(char *name, t_entries *last)
{
	t_entries *entries = (t_entries *)malloc(sizeof(t_entries));
	if (!entries)
		MALLOC_ERR();
	entries->name = ft_strdup(name);
	entries->stat_data = NULL;
	entries->prev = last;
	entries->next = NULL;

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