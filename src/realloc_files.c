/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:12:50 by rnovodra          #+#    #+#             */
/*   Updated: 2018/11/13 18:12:51 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		realloc_files(t_data *d)
{
	t_file	*tmp;

	if (!(tmp = ft_nrealloc((void*)d->files, sizeof(t_file) * d->files_used,
		sizeof(t_file) * (d->files_alloc * 2))))
		error(d);
	free(d->files);
	d->files_alloc *= 2;
	d->files = tmp;
}
