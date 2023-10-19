/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:39:39 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/19 03:19:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_object_list(t_l_obj *list)
{
	t_l_obj	*to_free;

	while (list)
	{
		to_free = list;
		list = list->next;
		free(to_free->object);
		free(to_free);
	}
}

bool	l_obj_add_back(t_l_obj **l_obj, void *object, t_obj_type type)
{
	t_l_obj	*new;

	new = malloc(sizeof(t_l_obj));
	if (!new)
		return (false);
	new->object = object;
	new->type = type;
	new->next = 0;
	new->is_selected = false;
	if (!*l_obj)
		*l_obj = new;
	else
		l_obj_last(*l_obj)->next = new;
	return (true);
}

t_l_obj	*l_obj_last(t_l_obj *l_obj)
{
	if (!l_obj)
		return (NULL);
	while (l_obj->next)
		l_obj = l_obj->next;
	return (l_obj);
}
