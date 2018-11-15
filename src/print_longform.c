/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_longform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:25:24 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/21 17:25:25 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	printtime(time_t ftime, bool sectime)
{
	char			*str_time;
	static time_t	now;
	char			*cp;
	int				*tmp;

	now == 0 ? now = time(NULL) : 0;
	str_time = ctime(&ftime) + 4;
	if (sectime)
		ft_printf("%.20s ", str_time);
	else if (ftime + SIXMONTHS > now && ftime < now + SIXMONTHS)
		ft_printf("%.12s ", str_time);
	else
	{
		cp = str_time;
		while (*cp && *cp != '\n')
			++cp;
		while (*cp != ' ')
			--cp;
		tmp = (int*)(cp + 1);
		while (*--cp != ' ')
			;
		*(cp + 1) = ' ';
		*(int*)(cp + 2) = *tmp;
		ft_printf("%.12s ", str_time);
	}
}

static inline char	extended_attr(t_file *f)
{
	acl_t		acl;
	acl_entry_t	dummy;
	const char	*name = f->realname ? f->realname : f->name;

	if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if (f->filetype == symbolic_link)
		acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	else
		acl = acl_get_file(name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl)
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}

static inline void	print_first_part(t_data *d, t_file *f)
{
	int		nminor;

	if (d->print_inode)
		ft_printf("%*d ", d->ino_w, f->stat.st_ino);
	if (d->print_block_size)
		ft_printf("%*d ", d->blksize_w, f->stat.st_blocks);
	mode(f->stat.st_mode);
	ft_printf("%c %*d ", extended_attr(f), d->nlink_w, f->stat.st_nlink);
	if (d->print_owner)
		ft_printf("%-*s  ", d->owner_w, getpwuid(f->stat.st_uid)->pw_name);
	if (d->print_group)
		ft_printf("%-*s  ", d->group_w, getgrgid(f->stat.st_gid)->gr_name);
	if (f->filetype == blockdev || f->filetype == chardev)
	{
		nminor = minor(f->stat.st_rdev);
		if (nminor > 255 || nminor < 0)
			ft_printf("%3d, 0x%08x ", major(f->stat.st_rdev), nminor);
		else
			ft_printf("%3d, %3d ", major(f->stat.st_rdev), nminor);
	}
	else
		ft_printf("%*d ", d->file_size_w, f->stat.st_size);
}

static inline void	print_last_part(t_data *d, t_file *f)
{
	int		color_printed;

	color_printed = 0;
	if (d->color)
		color_printed = set_color(f->filetype, f->stat.st_mode);
	ft_printf("%s", f->name);
	if (d->color && color_printed)
		ft_putstr("\e[0;00m");
	if (d->type)
		printtype(d->slash, f->stat.st_mode);
	if (f->linkname)
		ft_printf(" -> %s", f->linkname);
}

void				print_longform(t_data *d, t_file **sorted_files)
{
	int		i;
	t_file	*f;

	i = 0;
	while (i < d->files_used)
	{
		f = sorted_files[i];
		print_first_part(d, f);
		if (time_type == time_mtime)
			printtime(f->stat.st_mtimespec.tv_sec, d->sectime);
		else if (time_type == time_atime)
			printtime(f->stat.st_atimespec.tv_sec, d->sectime);
		else if (time_type == time_ctime)
			printtime(f->stat.st_ctimespec.tv_sec, d->sectime);
		else
			printtime(f->stat.st_birthtimespec.tv_sec, d->sectime);
		print_last_part(d, f);
		ft_putchar('\n');
		++i;
	}
}
