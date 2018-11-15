/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 12:18:39 by rnovodra          #+#    #+#             */
/*   Updated: 2018/09/25 12:18:40 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	calc_width(t_data *d, t_file *f)
{
	int		len;

	if ((len = ft_count_digits(f->stat.st_ino)) > d->inode_w)
		d->inode_w = len;
	if ((len = ft_count_digits(f->stat.st_nlink)) > d->nlink_w)
		d->nlink_w = len;
	if ((len = ft_strlen(getpwuid(f->stat.st_uid)->pw_name)) > d->owner_w)
		d->owner_w = len;
	if ((len = ft_strlen(getgrgid(f->stat.st_gid)->gr_name)) > d->group_w)
		d->group_w = len;
	if ((len = ft_count_digits(f->stat.st_size)) > d->file_size_w)
		d->file_size_w = len;
	if (f->filetype == blockdev || f->filetype == chardev)
	{
		if ((len = ft_count_digits(major(f->stat.st_rdev))) > d->major_w)
			d->major_w = len;
		if ((len = ft_count_digits(minor(f->stat.st_rdev))) > d->minor_w)
			d->minor_w = len;
		len = d->major_w + d->minor_w + 2;
		if (d->file_size_w < len)
			d->file_size_w = len;
	}
}

static inline void	get_filetype(t_file *file, mode_t st_mode,
					bool command_arg, bool immediate_dirs)
{
	st_mode &= S_IFMT;
	if (st_mode == S_IFIFO)
		file->filetype = fifo;
	else if (st_mode == S_IFCHR)
		file->filetype = chardev;
	else if (st_mode == S_IFDIR)
	{
		if (command_arg && !immediate_dirs)
			file->filetype = arg_directory;
		else
			file->filetype = directory;
	}
	else if (st_mode == S_IFBLK)
		file->filetype = blockdev;
	else if (st_mode == S_IFREG)
		file->filetype = normal;
	else if (st_mode == S_IFLNK)
		file->filetype = symbolic_link;
	else if (st_mode == S_IFSOCK)
		file->filetype = sock;
	else
		file->filetype = unknown;
}

static inline void	manage_link(t_data *d, t_file *f,
					const char *name, bool command_arg)
{
	struct stat	s_stat;

	if (!(f->linkname = ft_strnew(256)) ||
		(readlink(name, f->linkname, 256) < 0))
		error(d);
	if (command_arg && d->link_follow)
	{
		if (stat(f->name, &s_stat) != 0)
			error(d);
		if ((s_stat.st_mode & S_IFMT) == S_IFDIR)
		{
			f->stat = s_stat;
			f->filetype = arg_directory;
			free(f->realname);
			if (!(f->realname = ft_strdup(f->linkname)))
				error(d);
			ft_strdel(&f->linkname);
		}
	}
}

static inline void	get_info_file(t_data *d, t_file *f,
					const char *name, bool command_arg)
{
	int		len;

	get_filetype(f, f->stat.st_mode, command_arg, d->immediate_dirs);
	if (f->filetype == symbolic_link)
		manage_link(d, f, name, command_arg);
	if (d->longform && f->filetype && f->filetype != arg_directory)
		calc_width(d, f);
	if (d->print_block_size)
		if ((len = ft_count_digits(f->stat.st_blocks)) > d->blksize_w)
			d->blksize_w = len;
	if (d->print_inode)
		if ((len = ft_count_digits(f->stat.st_ino)) > d->ino_w)
			d->ino_w = len;
	d->files_used++;
}

uintmax_t			manage_file(t_data *d, const char *name,
					const char *dirname, bool command_arg)
{
	t_file	*f;
	char	*absolute_name;

	if (d->files_alloc == d->files_used)
		realloc_files(d);
	f = &d->files[d->files_used];
	ft_memset(f, 0, sizeof(t_file));
	if (name[0] == '/' || !dirname || dirname[0] == 0)
		absolute_name = (char*)name;
	else
	{
		absolute_name = (char*)malloc(ft_strlen(name) +
			ft_strlen(dirname) + 2);
		attach(absolute_name, dirname, name);
		f->realname = absolute_name;
	}
	(!(f->name = ft_strdup(name))) ? error(d) : 0;
	if (lstat(absolute_name, &f->stat) != 0 && (ENOENT != errno || !d->sfunc))
	{
		free(f->realname);
		ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno));
		return (0);
	}
	get_info_file(d, f, absolute_name, command_arg);
	return (f->stat.st_blocks);
}
