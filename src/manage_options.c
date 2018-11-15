/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 16:50:34 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/16 16:50:35 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline int	options_last(t_data *d, char op)
{
	if (op == '1')
	{
		d->singlecol = true;
		d->longform = false;
		d->commas = false;
	}
	else if (op == 'C' || op == 'x' || op == 'm')
	{
		if (op == 'x')
			d->colacross = false;
		else if (op == 'C')
			d->colacross = true;
		else
			d->commas = true;
		d->longform = false;
		d->singlecol = false;
	}
	else if (op == 'H')
		d->link_follow = true;
	else
	{
		ft_printf("ft_ls: illegal option -- %c\n", op);
		return (-1);
	}
	return (0);
}

static inline int	options_one_more(t_data *d, char op)
{
	if (op == 'S')
		d->sort_size = true;
	else if (op == 't')
		d->sort_time = true;
	else if (op == 'T')
		d->sectime = true;
	else if (op == 'd')
		d->immediate_dirs = true;
	else if (op == 'i')
		d->print_inode = true;
	else if (op == 'r')
		d->reverse = true;
	else if (op == 'g' || op == 'o')
	{
		d->longform = true;
		if (op == 'g')
			d->print_owner = false;
		else
			d->print_group = false;
	}
	else if (op == 'G')
		setenv("CLICOLOR", "", 1);
	else if (options_last(d, op) < 0)
		return (-1);
	return (0);
}

static inline int	options_again(t_data *d, char op)
{
	if (op == 'F')
	{
		d->slash = 0;
		d->type = true;
	}
	else if (op == 's')
		d->print_block_size = true;
	else if (op == 'p')
	{
		d->slash = true;
		d->type = true;
	}
	else if (op == 'u')
		time_type = time_atime;
	else if (op == 'U')
		time_type = time_btime;
	else if (op == 'c')
		time_type = time_ctime;
	else if (options_one_more(d, op) < 0)
		return (-1);
	return (0);
}

static inline int	options(t_data *d, char *av)
{
	char	op;

	while (*++av)
	{
		op = *av;
		if (op == 'R')
			d->recursive = true;
		else if (op == 'l')
		{
			d->longform = true;
			d->commas = false;
			d->singlecol = false;
		}
		else if (op == 'a')
			d->dot_files = true;
		else if (op == 'f')
		{
			d->nonsort = true;
			d->dot_files = true;
		}
		else if (options_again(d, op) < 0)
			return (-1);
	}
	return (0);
}

int					manage_options(t_data *d, char **av)
{
	size_t	i;

	i = 1;
	while (av[i] && *av[i] == '-' && *(av[i] + 1))
	{
		if (options(d, av[i]) < 0)
			return (-1);
		++i;
	}
	return (i);
}
