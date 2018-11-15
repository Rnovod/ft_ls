/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:08:43 by rnovodra          #+#    #+#             */
/*   Updated: 2018/11/11 19:08:44 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline int	set_color_exec(u_int mode)
{
	if (mode & S_ISUID)
		ft_putstr("\e[0;41;30m");
	else if (mode & S_ISGID)
		ft_putstr("\e[0;46;30m");
	else
		ft_putstr("\e[0;31m");
	return (1);
}

int					set_color(t_filetype filetype, u_int mode)
{
	if (filetype >= directory)
	{
		if (mode & S_IWOTH)
		{
			if (mode & S_ISTXT)
				ft_putstr("\e[0;42;30m");
		}
		else
			ft_putstr("\e[0;34m");
	}
	else if (filetype == symbolic_link)
		ft_putstr("\e[0;35m");
	else if (filetype == sock)
		ft_putstr("\e[0;32m");
	else if (filetype == fifo)
		ft_putstr("\e[0;33m");
	else if (filetype == blockdev)
		ft_putstr("\e[0;46;34m");
	else if (filetype == chardev)
		ft_putstr("\e[0;43;34m");
	else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		set_color_exec(mode);
	else
		return (0);
	return (1);
}
