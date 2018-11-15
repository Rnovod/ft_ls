/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printname.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:36:13 by rnovodra          #+#    #+#             */
/*   Updated: 2018/11/13 17:36:13 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		printname(t_data *d, t_file *f)
{
	int	chcnt;
	int	color_printed;

	color_printed = 0;
	chcnt = 0;
	if (d->print_inode)
		chcnt += ft_printf("%*lu ", d->ino_w, f->stat.st_ino);
	if (d->print_block_size)
		chcnt += ft_printf("%*jd ", d->blksize_w, f->stat.st_blocks);
	if (d->color)
		color_printed = set_color(f->filetype, f->stat.st_mode);
	chcnt += ft_printf("%s", f->name);
	if (d->color && color_printed)
		ft_putstr("\e[0;00m");
	if (d->type)
		chcnt += printtype(d->slash, f->stat.st_mode);
	return (chcnt);
}
