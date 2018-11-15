/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:53:56 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/20 18:53:57 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_current_files(t_data *d)
{
	int		i;
	t_file	**sorted;
	t_file	**tmp;
	t_file	*f;

	sorted = d->sorted_files;
	tmp = sorted;
	i = 0;
	while (i < d->files_used)
	{
		f = sorted[i];
		if (f->filetype != unknown)
			break ;
		if (f->realname)
			ft_dprintf(2, "ft_ls: %s: No such file or directory\n",
			f->realname);
		else
			ft_dprintf(2, "ft_ls: %s: No such file or directory\n", f->name);
		i++;
	}
	d->files_used -= i;
	d->pfunc(d, &sorted[i]);
	d->files_used += i;
}
