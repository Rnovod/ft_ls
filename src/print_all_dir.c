/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:49:49 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/26 16:49:50 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline const char	*cut_name(char const *name)
{
	size_t		len;
	const char	*cp;

	if (name)
	{
		len = ft_strlen(name);
		cp = name;
		name += len - 1;
		while (*name != '/' && name > cp)
			--name;
		return (name == cp ? name : name + 1);
	}
	return (0);
}

static inline uintmax_t		read_files_from_dir(t_data *d, DIR *dir,
							const char *name)
{
	struct dirent	*next;
	uintmax_t		total_blocks;

	total_blocks = 0;
	while (1)
	{
		errno = 0;
		next = readdir(dir);
		if (next)
		{
			if ((next->d_name[0] == '.' && d->dot_files) ||
				next->d_name[0] != '.')
				total_blocks += manage_file(d, next->d_name, name, false);
		}
		else if (errno != 0)
		{
			ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno));
			if (errno != EOVERFLOW)
				break ;
		}
		else
			break ;
	}
	return (total_blocks);
}

static inline void			print_dir(t_data *d, const char *name,
							bool command_arg)
{
	DIR				*dir;
	uintmax_t		total_blocks;

	clear_files(d);
	if (d->print_dir_name)
		ft_printf("%s:\n", name);
	if (!(dir = opendir(name)))
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", cut_name(name), strerror(errno));
		return ;
	}
	total_blocks = read_files_from_dir(d, dir, name);
	if (closedir(dir) != 0)
		ft_printf("Can't close the directory %s\n", name);
	sort_files(d, d->sfunc);
	if (d->recursive)
		extract_dirs_from_files(d, name, command_arg);
	if (d->longform || (d->print_block_size && !d->commas))
		if (d->files_used)
			ft_printf("total %d\n", total_blocks);
	if (d->files_used)
		print_current_files(d);
}

void						print_all_dir(t_data *d)
{
	t_pend	*thispend;
	bool	first;

	first = true;
	while (d->queue_dir)
	{
		thispend = d->queue_dir;
		d->queue_dir = d->queue_dir->next;
		if (!first)
			ft_putchar('\n');
		first = false;
		print_dir(d, thispend->name, thispend->command_arg);
		free(thispend->name);
		free(thispend->realname);
		free(thispend);
		d->print_dir_name = true;
	}
}
