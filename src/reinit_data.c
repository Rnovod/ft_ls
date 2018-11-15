/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinit_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:28:32 by rnovodra          #+#    #+#             */
/*   Updated: 2018/11/13 15:28:33 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	set_sort_fuc(t_data *d)
{
	if (d->nonsort)
		d->sfunc = NULL;
	else if (d->reverse)
	{
		if (d->sort_size)
			d->sfunc = rev_sort_by_size;
		else if (d->sort_time)
			d->sfunc = rev_sort_by_time;
		else
			d->sfunc = rev_sort_by_ascii;
	}
	else
	{
		if (d->sort_size)
			d->sfunc = sort_by_size;
		else if (d->sort_time)
			d->sfunc = sort_by_time;
		else
			d->sfunc = sort_by_ascii;
	}
}

void				reinit_data(t_data *d)
{
	if (getenv("CLICOLOR") &&
		(isatty(STDOUT_FILENO) || getenv("CLICOLOR_FORCE")))
	{
		d->notabs = true;
		d->color = 1;
	}
	if (d->immediate_dirs)
		d->recursive = false;
	d->print_dir_name = true;
	if (d->longform)
		d->pfunc = print_longform;
	else if (d->singlecol)
		d->pfunc = print_singlecol;
	else if (d->commas)
		d->pfunc = print_commas;
	else
		d->pfunc = print_cols;
	if (!d->longform && !d->immediate_dirs && !d->type && !d->print_inode)
		d->link_follow = true;
	set_sort_fuc(d);
}
