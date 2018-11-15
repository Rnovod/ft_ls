/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:15:31 by rnovodra          #+#    #+#             */
/*   Updated: 2018/10/24 16:15:33 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		queue_dir(t_data *d, const char *name, const char *realname,
			bool command_arg)
{
	t_pend	*new;

	if (!(new = (t_pend*)malloc(sizeof(t_pend))))
		error(d);
	new->name = name ? ft_strdup(name) : NULL;
	new->realname = realname ? ft_strdup(realname) : NULL;
	if (name && !new->name)
		error(d);
	if (realname && !new->realname)
		error(d);
	new->command_arg = command_arg;
	new->next = d->queue_dir;
	d->queue_dir = new;
}
