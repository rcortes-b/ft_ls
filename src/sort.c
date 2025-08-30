#include "../inc/sort.h"
#include "../inc/list.h"
#include "../inc/utils.h"
#

static void	split_into_halfes(struct s_entries *head, struct s_entries **left, struct s_entries **right)
{
	t_entries *fast = head->next;
	t_entries *slow = head;

	while(fast) {
		fast = fast->next;
		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*left = head;
	*right = slow->next;
	slow->next = NULL;
}

static struct s_entries *merge_by_mt(struct s_entries *left, struct s_entries *right, bool is_reversed)
{
	t_entries *res;

	if (!left)
		return right;
	else if (!right)
		return left;
	if (!is_reversed) {
		if (left->stat_data->st_mtime > right->stat_data->st_mtime) {
			res = left;
			res->next = merge_by_mt(left->next, right, is_reversed);
		} else {
			res = right;
			res->next = merge_by_mt(left, right->next, is_reversed);
		}
	} else {
		if (left->stat_data->st_mtime < right->stat_data->st_mtime) {
			res = left;
			res->next = merge_by_mt(left->next, right, is_reversed);
		} else {
			res = right;
			res->next = merge_by_mt(left, right->next, is_reversed);
		}	
	}

	return res;
}

static struct s_entries *merge_by_alphabet(struct s_entries *left, struct s_entries *right, bool is_reversed)
{
	t_entries *res;

	if (!left)
		return right;
	else if (!right)
		return left;

	int compare_value = ft_strcmp(left->name, right->name);

	if (!is_reversed) {
		if (compare_value < 0) {
			res = left;
			res->next = merge_by_alphabet(left->next, right, is_reversed);
		} else {
			res = right;
			res->next = merge_by_alphabet(left, right->next, is_reversed);
		}
	} else {
		if (compare_value > 0) {
			res = left;
			res->next = merge_by_alphabet(left->next, right, is_reversed);
		} else {
			res = right;
			res->next = merge_by_alphabet(left, right->next, is_reversed);
		}	
	}

	return res;
}

void	merge_sort(struct s_entries **head, struct s_options opt)
{
	t_entries	*left;
	t_entries	*right;
	t_entries	*headRef = *head;

	if (!headRef || !headRef->next)
		return ;
	
	split_into_halfes(headRef, &left, &right);

	merge_sort(&left, opt);
	merge_sort(&right, opt);
	if (!opt.time)
		*head = merge_by_alphabet(left, right, opt.reverse);
	else
		*head = merge_by_mt(left, right, opt.reverse);
}