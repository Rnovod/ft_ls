/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:16:05 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/22 14:16:05 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clear_files(t_data *d)
{
	int		i;
	t_file	*f;
	t_file	**sorted;

	i = 0;
	sorted = d->sorted_files;
	while (i < d->files_used)
	{
		f = sorted[i];
		free(f->name);
		free(f->realname);
		free(f->linkname);
		i++;
	}
	d->files_used = 0;
	d->inode_w = 0;
	d->nlink_w = 0;
	d->owner_w = 0;
	d->group_w = 0;
	d->major_w = 0;
	d->minor_w = 0;
	d->file_size_w = 0;
	d->blksize_w = 0;
	d->ino_w = 0;
	d->file_size_w = 0;
}
