/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:42:57 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/17 11:42:58 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_files(t_data *d)
{
	int		i;
	t_file	*f;

	i = 0;
	if (d->files)
	{
		if (d->sorted_files)
			free(d->sorted_files);
		while (i < d->files_used)
		{
			f = &d->files[i];
			free(f->name);
			free(f->realname);
			free(f->linkname);
			++i;
		}
		free(d->files);
	}
}

void	error(t_data *d)
{
	free_files(d);
	ft_dprintf(2, "ft_ls: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
