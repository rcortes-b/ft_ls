#include "../inc/print.h"
#include "../inc/utils.h"

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

static void	print_entry_as_list(t_entries *entry, t_padding w_padding)
{
	size_t padding;
	ft_printf("%s ", get_mode(entry->stat_data->st_mode));

	padding = w_padding.nlink - number_len(entry->stat_data->st_nlink);
	while (padding-- > 0)
		write(1, " ", 1);
	ft_printf("%d ", entry->stat_data->st_nlink);

	padding = w_padding.pwusize - ft_strlen(getpwuid(entry->stat_data->st_uid)->pw_name);
	while (padding-- > 0)
		write(1, " ", 1);
	ft_printf("%s ", getgrgid(entry->stat_data->st_gid)->gr_name);

	padding = w_padding.pwusize - ft_strlen(getpwuid(entry->stat_data->st_uid)->pw_name);
	while (padding-- > 0)
		write(1, " ", 1);
	ft_printf("%s ", getgrgid(entry->stat_data->st_gid)->gr_name);

	padding = w_padding.filesize - number_len((int)entry->stat_data->st_size);
	while (padding-- > 0)
		write(1, " ", 1);
	ft_printf("%d ", entry->stat_data->st_size);

	ft_printf("%s ", modify_date(ctime(&entry->stat_data->st_mtime)));
	ft_printf("%s", entry->name);
	if (entry->next)
		ft_printf("\n");

}

static void print_entry(char *str, size_t *counter, size_t max_size)
{
	size_t padding;
	padding = max_size - ft_strlen(str);
	if (WIDTH / max_size == *counter) {
		write(1, "\n", 1);
		*counter = 0;
	}
	ft_printf("%s", str);
	while (padding-- > 0)
		write(1, " ", 1);
	
	*counter += 1;
}

static t_padding get_padding_size(t_entries *entries)
{
	t_entries	*tmp;
	t_padding	padding;
	size_t		value;
	
	tmp = entries;
	padding.nlink = 1;
	padding.pwusize = 0;
	padding.grpsize = 0;
	padding.filesize = 0;
	while (tmp) {
		value = number_len((int)tmp->stat_data->st_nlink);
		if (value > padding.nlink)
			padding.nlink = value;
		value = ft_strlen(getpwuid(tmp->stat_data->st_uid)->pw_name);
		if (value > padding.pwusize)
			padding.pwusize = value;
		value = ft_strlen(getgrgid(tmp->stat_data->st_gid)->gr_name);
		if (value > padding.grpsize)
			padding.grpsize = value;
		value = number_len((int)tmp->stat_data->st_size);
		if (value > padding.filesize)
			padding.filesize = value;
		tmp = tmp->next;
	}
	return padding;
}

void	print_list(struct s_list **list, struct s_options opt, size_t amount)
{
	t_list		*lst;
	t_entries	*entry;
	t_padding	padding;
	size_t		counter;

	lst = *list;
	while (lst) {
		if (opt.recursive || amount > 1)
			ft_printf("%s:\n", lst->name);
		if (opt.list) {
			ft_printf("total %d\n", get_total_block_size(lst->entries) / 2);
			padding = get_padding_size(lst->entries);
		}
		entry = lst->entries;
		lst->highest_nsize += 2;
		counter = 0;
		while (entry) {
			if (!opt.list)
				print_entry(entry->name, &counter, lst->highest_nsize);
			else
				print_entry_as_list(entry, padding);
			entry = entry->next;
		}
		write(1, "\n", 1);
		if (lst->next)
			write(1, "\n", 1);
		lst = lst->next;
	}
}
