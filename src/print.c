#include "../inc/print.h"
#include <time.h>

static char *modify_date(char *date)
{
	date = &date[4];
	size_t i = 0;
	while (date[i] != ':')
		i++;
	i += 3;
	date[i] = '\0';
	return date;
}

static char get_object_type(mode_t mode)
{
	if ((mode & __S_IFMT) == __S_IFREG)
		return '-';
	else if ((mode & __S_IFMT) == __S_IFDIR)
		return 'd';
	else if ((mode & __S_IFMT) == __S_IFBLK)
		return 'b';
	else if ((mode & __S_IFMT) == __S_IFCHR)
		return 'c';
	else if ((mode & __S_IFMT) == __S_IFIFO)
		return 'p';
	else if ((mode & __S_IFMT) == __S_IFLNK)
		return 'l';
	else if ((mode & __S_IFMT) == __S_IFSOCK)
		return 's';
	return ' ';
}

static char get_mode_letter(mode_t mode)
{
	if (mode == S_IRUSR || mode == S_IRGRP || mode == S_IROTH)
		return 'r';
	else if (mode == S_IWUSR || mode == S_IWGRP || mode == S_IWOTH)
		return 'w';
	else
		return 'x';	
}

static char *get_mode(mode_t mode)
{
	static char str_mode[11];
	mode_t mode_permissions[9] = {S_IRUSR, S_IWUSR, S_IXUSR,
									S_IRGRP, S_IWGRP, S_IXGRP,
									S_IROTH, S_IWOTH, S_IXOTH};
	size_t counter = 0;
	str_mode[counter++] = get_object_type(mode);
	while (counter - 1 < 9) {
		if (mode & mode_permissions[counter - 1])
			str_mode[counter] = get_mode_letter(mode_permissions[counter - 1]);
		else
			str_mode[counter] = '-';
		counter++;
	}
	str_mode[counter] = '\0';
	return (str_mode);
}

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
	ft_printf("%s ", get_mode(entry->stat_data->st_mode));
	ft_printf("%d ", entry->stat_data->st_nlink);
	ft_printf("%s ", getpwuid(entry->stat_data->st_uid)->pw_name);
	ft_printf("%s ", getgrgid(entry->stat_data->st_gid)->gr_name);
	ft_printf("%d ", entry->stat_data->st_size);
	ft_printf("%s ", modify_date(ctime(&entry->stat_data->st_mtime)));
	ft_printf("%s\n", entry->name);

}

void	print_list(struct s_list **list, t_options opt, size_t amount)
{
	t_list *lst = *list;
	t_entries *entry;
	while (lst) {
		if (opt.recursive || amount > 1)
			ft_printf("%s:\n", lst->name);
		if (opt.list)
			ft_printf("total %d\n", get_total_block_size(lst->entries) / 2);
		entry = lst->entries;
		while (entry) {
			if (!opt.list)
				ft_printf("%s ", entry->name);
			else
				print_entry_as_list(entry);
			entry = entry->next;
		}
		if (!opt.list)
			ft_printf("\n");
		if (opt.recursive)
			ft_printf("\n");
		lst = lst->next;
	}
}
