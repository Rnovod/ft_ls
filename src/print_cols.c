/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cols.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:25:53 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/21 17:25:54 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	print_files(t_data *d, int cols, int rows, int colwidth)
{
	int		i;
	t_file	*f;
	int		col;
	int		row;
	int		spaces;

	i = 0;
	row = -1;
	while (++row < rows)
	{
		col = 0;
		if (d->colacross)
			i = row;
		while (1)
		{
			f = d->sorted_files[i];
			spaces = colwidth - printname(d, f);
			i += (!d->colacross) ? 1 : rows;
			if (i >= d->files_used || ++col >= cols)
				break ;
			while (spaces--)
				write(1, " ", 1);
		}
		ft_putchar('\n');
	}
}

static inline int	maxlen_file(t_data *d, t_file **sorted_files)
{
	int		len;
	int		maxname_len;
	int		i;
	t_file	*f;

	i = 0;
	maxname_len = 0;
	while (i < d->files_used)
	{
		len = 0;
		f = sorted_files[i];
		if (d->print_inode)
			len += 1 + d->ino_w;
		if (d->print_block_size)
			len += 1 + d->blksize_w;
		if (d->type)
			len += 1;
		len += ft_strlen(f->name);
		if (maxname_len < len)
			maxname_len = len;
		i++;
	}
	return (maxname_len);
}

void				print_cols(t_data *d, t_file **sorted_files)
{
	int		colwidth;
	int		rows;
	int		cols;
	int		tabwidth;
	t_file	**tmp;

	if (d->notabs)
		tabwidth = 1;
	else
		tabwidth = 8;
	colwidth = maxlen_file(d, sorted_files);
	colwidth = ((colwidth + tabwidth) & ~(tabwidth - 1));
	cols = d->termwidth / colwidth;
	if ((int)d->termwidth < 2 * colwidth)
	{
		print_singlecol(d, sorted_files);
		return ;
	}
	rows = (d->files_used % cols != 0) + d->files_used / cols;
	tmp = d->sorted_files;
	d->sorted_files = sorted_files;
	print_files(d, cols, rows, colwidth);
	d->sorted_files = tmp;
}
