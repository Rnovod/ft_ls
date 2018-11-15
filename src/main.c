/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:42:52 by rnovodra          #+#    #+#             */
/*   Updated: 2018/09/24 19:42:53 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	get_termwidth(t_data *d)
{
	char			*p;
	struct winsize	win;

	d->termwidth = 80;
	if (isatty(STDOUT_FILENO))
	{
		if ((p = getenv("COLUMNS")) != NULL && *p != '\0')
			d->termwidth = ft_atoi(p);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) != -1 &&
			win.ws_col > 0)
			d->termwidth = win.ws_col;
	}
	else
	{
		d->pfunc = print_longform;
		p = getenv("COLUMNS");
		if (p)
			d->termwidth = ft_atoi(p);
	}
}

static inline void	init_default_data(t_data *d)
{
	time_type = time_mtime;
	d->colacross = true;
	d->files_alloc = 100;
	d->print_owner = true;
	d->print_group = true;
	errno = 0;
	if (!(d->files = (t_file*)malloc(sizeof(t_file) * d->files_alloc)))
		error(d);
	get_termwidth(d);
}

static inline void	work_files(t_data *d, int n_files)
{
	if (d->files_used)
	{
		sort_files(d, d->sfunc);
		if (!d->immediate_dirs)
			extract_dirs_from_files(d, NULL, true);
	}
	if (d->files_used)
	{
		print_current_files(d);
		if (d->queue_dir &&
			d->sorted_files[d->files_used - 1]->filetype != unknown)
			ft_putchar('\n');
	}
	else if (n_files <= 1 && d->queue_dir && !d->queue_dir->next)
		d->print_dir_name = false;
	print_all_dir(d);
	free_files(d);
}

int					main(const int ac, char **av)
{
	t_data	d;
	int		i;
	int		n_files;

	ft_bzero(&d, sizeof(t_data));
	init_default_data(&d);
	if ((i = manage_options(&d, av)) < 0)
	{
		ft_putendl("usage: ft_ls [-FGHCRSTUacdfgilmoprstux1] [file ...]");
		return (-1);
	}
	n_files = ac - i;
	reinit_data(&d);
	if (n_files <= 0)
	{
		if (d.immediate_dirs)
			manage_file(&d, ".", "", true);
		else
			queue_dir(&d, ".", NULL, true);
	}
	else
		while (i < ac)
			manage_file(&d, av[i++], "", true);
	work_files(&d, n_files);
	return (0);
}
