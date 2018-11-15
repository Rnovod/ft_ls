/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_singlecol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:25:33 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/21 17:25:33 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_singlecol(t_data *d, t_file **sorted_files)
{
	t_file	*f;
	int		i;

	i = 0;
	while (i < d->files_used)
	{
		f = sorted_files[i];
		printname(d, f);
		ft_putchar('\n');
		++i;
	}
}
