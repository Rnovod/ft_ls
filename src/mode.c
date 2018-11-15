/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:51:31 by rnovodra          #+#    #+#             */
/*   Updated: 2018/09/25 15:51:32 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	mode_type(char *restrict mode, mode_t st_mode)
{
	st_mode &= S_IFMT;
	if (st_mode == S_IFIFO)
		*mode = 'p';
	else if (st_mode == S_IFCHR)
		*mode = 'c';
	else if (st_mode == S_IFDIR)
		*mode = 'd';
	else if (st_mode == S_IFBLK)
		*mode = 'b';
	else if (st_mode == S_IFREG)
		*mode = '-';
	else if (st_mode == S_IFLNK)
		*mode = 'l';
	else if (st_mode == S_IFSOCK)
		*mode = 's';
}

static inline void	mode_permission(char *restrict mode, mode_t st_mode)
{
	++mode;
	*mode++ = st_mode & S_IRUSR ? 'r' : '-';
	*mode++ = st_mode & S_IWUSR ? 'w' : '-';
	if (st_mode & S_ISUID)
		*mode++ = st_mode & S_IXUSR ? 's' : 'S';
	else
		*mode++ = st_mode & S_IXUSR ? 'x' : '-';
	*mode++ = st_mode & S_IRGRP ? 'r' : '-';
	*mode++ = st_mode & S_IWGRP ? 'w' : '-';
	if (st_mode & S_ISGID)
		*mode++ = st_mode & S_IXGRP ? 's' : 'S';
	else
		*mode++ = st_mode & S_IXGRP ? 'x' : '-';
	*mode++ = st_mode & S_IROTH ? 'r' : '-';
	*mode++ = st_mode & S_IWOTH ? 'w' : '-';
	if (st_mode & S_ISVTX)
		*mode++ = st_mode & S_IXOTH ? 't' : 'T';
	else
		*mode++ = st_mode & S_IXOTH ? 'x' : '-';
	*mode = '\0';
}

void				mode(mode_t st_mode)
{
	char	mode[12];

	mode_type(mode, st_mode);
	mode_permission(mode, st_mode);
	ft_putstr(mode);
}
