/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:36:06 by rnovodra          #+#    #+#             */
/*   Updated: 2018/11/13 17:36:07 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		printtype(bool slash, u_int mode)
{
	u_int	f_mode;

	f_mode = mode & S_IFMT;
	if (slash)
	{
		if (f_mode == S_IFDIR)
			ft_putchar('/');
		else
			return (0);
	}
	else if (f_mode == S_IFDIR)
		ft_putchar('/');
	else if (f_mode == S_IFIFO)
		ft_putchar('|');
	else if (f_mode == S_IFLNK)
		ft_putchar('@');
	else if (f_mode == S_IFSOCK)
		ft_putchar('=');
	else if (f_mode == S_IFWHT)
		ft_putchar('%');
	else if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		ft_putchar('*');
	else
		return (0);
	return (1);
}
