/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:43:19 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/27 13:43:20 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	attach(char *dest, const char *dirname, const char *name)
{
	const char *dirnamep = dirname;

	while (*dirnamep)
		*dest++ = *dirnamep++;
	if (dirnamep > dirname && dirnamep[-1] != '/')
		*dest++ = '/';
	while (*name)
		*dest++ = *name++;
	*dest = 0;
}
