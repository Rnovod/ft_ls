/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:29:11 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/18 12:29:12 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline int	part(t_file **files, int low, int high, t_sortfunc *func)
{
	int pivot;
	int i;
	int j;

	pivot = high;
	i = low - 1;
	j = low;
	while (j <= high - 1)
	{
		if (func(files[j], files[pivot]) < 0)
		{
			i++;
			SWAP(files[i], files[j], t_file*);
		}
		++j;
	}
	SWAP(files[i + 1], files[high], t_file*);
	return (i + 1);
}

static void			fqsort(t_file **files, int low, int high, t_sortfunc *func)
{
	int pivot;

	if (low < high)
	{
		pivot = part(files, low, high, func);
		fqsort(files, low, pivot - 1, func);
		fqsort(files, pivot + 1, high, func);
	}
}

void				sort_files(t_data *d, t_sortfunc *func)
{
	int		i;
	t_file	**sorted_files;

	if (d->sorted_alloc < d->files_used + d->files_used / 2)
	{
		free(d->sorted_files);
		if (!(d->sorted_files = (t_file**)malloc(sizeof(t_file*) *
			d->files_used * 3)))
			error(d);
		d->sorted_alloc = d->files_used * 3;
	}
	sorted_files = d->sorted_files;
	i = 0;
	while (i < d->files_used)
	{
		sorted_files[i] = &d->files[i];
		++i;
	}
	if (!func)
		return ;
	fqsort(sorted_files, 0, d->files_used - 1, func);
}
