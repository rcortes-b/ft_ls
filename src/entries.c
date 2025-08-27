#include "../inc/ls.h"
#include "../inc/list.h"
#include "../inc/err.h"

t_entries *get_entries(DIR *root)
{
	t_entries *entries = (t_entries *)malloc(sizeof(t_entries));
	if (!entries)
		MALLOC_ERR();
	//first of all ive to do new list functions
}

t_list *get_list(char *root)
{
	t_list	*new_lst = (t_list*)malloc(sizeof(new_lst));
	if (!new_lst)
		MALLOC_ERR();
	new_lst->name = ft_strdup(root);
	new_lst->root = opendir(root);
	if (!new_lst->root) {
		strerror(errno);
		return NULL;
	}
} 