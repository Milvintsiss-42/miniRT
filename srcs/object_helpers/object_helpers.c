/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:50:07 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 11:32:39 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_l_obj	*select_object_at_screen_coord(t_mrt *mrt, int x, int y)
{
	t_ray		ray;
	t_intersect	intersect;

	ray.origin = mrt->scene.camera.origin;
	ray.dir = get_ray_direction(mrt, x, y);
	intersect = closest_intersection(mrt, ray, 1.0, __DBL_MAX__);
	if (!intersect.obj)
		return (NULL);
	intersect.obj->is_selected = !intersect.obj->is_selected;
	return (intersect.obj);
}

void	apply_modifier_to_selected_objs(t_mrt *mrt,
	void (*modifier)(t_mrt *mrt, t_l_obj *obj, int direction),
	int direction)
{
	t_l_obj	*iter_obj;

	iter_obj = mrt->scene.objects;
	while (iter_obj)
	{
		if (iter_obj->is_selected)
			modifier(mrt, iter_obj, direction);
		iter_obj = iter_obj->next;
	}
	iter_obj = mrt->scene.lights;
	while (iter_obj)
	{
		if (iter_obj->is_selected)
			modifier(mrt, iter_obj, direction);
		iter_obj = iter_obj->next;
	}
}
