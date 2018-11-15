/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:48:48 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/18 11:48:48 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_by_size(const t_file *restrict f1, const t_file *restrict f2)
{
	int	diff;

	if (f1->filetype == unknown && f2->filetype == unknown)
		return (ft_strcmp(f1->name, f2->name));
	if (f1->filetype == unknown)
		return (-1);
	if (f2->filetype == unknown)
		return (1);
	diff = f2->stat.st_size - f1->stat.st_size;
	return (diff ? diff : ft_strcmp(f1->name, f2->name));
}

int		sort_by_time(const t_file *restrict f1, const t_file *restrict f2)
{
	int	diff;

	if (f1->filetype == unknown && f2->filetype == unknown)
		return (ft_strcmp(f1->name, f2->name));
	if (f1->filetype == unknown)
		return (-1);
	if (f2->filetype == unknown)
		return (1);
	if (time_type == time_mtime)
		diff = f2->stat.st_mtimespec.tv_sec - f1->stat.st_mtimespec.tv_sec;
	else if (time_type == time_ctime)
		diff = f2->stat.st_ctimespec.tv_sec - f1->stat.st_ctimespec.tv_sec;
	else if (time_type == time_btime)
		diff = f2->stat.st_birthtimespec.tv_sec -
		f1->stat.st_birthtimespec.tv_sec;
	else
		diff = f2->stat.st_atimespec.tv_sec - f1->stat.st_atimespec.tv_sec;
	return (diff ? diff : ft_strcmp(f1->name, f2->name));
}

int		sort_by_ascii(const t_file *restrict f1, const t_file *restrict f2)
{
	if (f1->filetype == unknown && f2->filetype == unknown)
		return (ft_strcmp(f1->name, f2->name));
	if (f1->filetype == unknown)
		return (-1);
	if (f2->filetype == unknown)
		return (1);
	return (ft_strcmp(f1->name, f2->name));
}
