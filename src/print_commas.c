/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:26:00 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/21 17:26:00 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_commas(t_data *d, t_file **sorted_files)
{
	int		i;
	t_file	*f;
	int		rowwidth;

	rowwidth = 0;
	i = 0;
	while (i < d->files_used)
	{
		f = sorted_files[i++];
		if ((int)ft_strlen(f->name) + rowwidth +
			(i < d->files_used ? 2 : 0) >= d->termwidth)
		{
			ft_putchar('\n');
			rowwidth = 0;
		}
		rowwidth += printname(d, f);
		if (i < d->files_used)
		{
			ft_putstr(", ");
			rowwidth += 2;
		}
	}
	if (rowwidth)
		ft_putchar('\n');
}
