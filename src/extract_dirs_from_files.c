/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_dirs_from_files.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:00:14 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/26 15:00:15 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	delete_dirs_from_table(t_data *d)
{
	int		i;
	int		j;
	t_file	**sorted_files;
	t_file	*f;

	j = 0;
	i = 0;
	sorted_files = d->sorted_files;
	while (i < d->files_used)
	{
		f = sorted_files[i];
		sorted_files[j] = f;
		j += (f->filetype != arg_directory);
		++i;
	}
	d->files_used = j;
}

static inline void	file_name_concat(t_data *d, const char *dirname, t_file *f,
					bool command_arg)
{
	char	*name;

	if (!(name = (char*)malloc(ft_strlen(f->name) + ft_strlen(dirname) + 2)))
		error(d);
	attach(name, dirname, f->name);
	queue_dir(d, name, f->linkname, command_arg);
	free(name);
}

static inline bool	name_dot_and_dot_dot(t_data *d, char *name)
{
	if (name[0] != '.')
		return (false);
	if (!d->dot_files)
		return (false);
	if ((name[0] == '.' && name[1] == '\0') ||
		(name[0] == '.' && name[1] == '.' && name[2] == '\0'))
		return (true);
	return (false);
}

void				extract_dirs_from_files(t_data *d, const char *dirname,
					bool command_arg)
{
	t_file		*f;
	t_file		**sorted_files;
	int			i;
	const bool	ignor = (dirname != NULL);

	i = d->files_used;
	sorted_files = d->sorted_files;
	while (i-- != 0)
	{
		f = sorted_files[i];
		if ((!ignor || !name_dot_and_dot_dot(d, f->name))
			&& (f->filetype == directory ||
			f->filetype == arg_directory))
		{
			if (!dirname || f->name[0] == '/')
				queue_dir(d, f->name, f->linkname, command_arg);
			else
				file_name_concat(d, dirname, f, command_arg);
			if (f->filetype == arg_directory)
				free(f->name);
		}
	}
	delete_dirs_from_table(d);
}
