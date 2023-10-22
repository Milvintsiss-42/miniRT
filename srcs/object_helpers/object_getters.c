/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 08:34:05 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 08:53:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_vec3	*get_obj_origin(t_l_obj *obj)
{
	if (obj->type == SPHERE)
		return (&((t_sphere *)obj->object)->origin);
	else if (obj->type == PLANE)
		return (&((t_plane *)obj->object)->origin);
	else if (obj->type == CYLINDER)
		return (&((t_cylinder *)obj->object)->origin);
	else if (obj->type == SPOT_LIGHT)
		return (&((t_light *)obj->object)->origin_o_dir);
	return (NULL);
}

t_vec3	*get_obj_orientation(t_l_obj *obj)
{
	if (obj->type == PLANE)
		return (&((t_plane *)obj->object)->orientation);
	else if (obj->type == CYLINDER)
		return (&((t_cylinder *)obj->object)->orientation);
	else if (obj->type == DIR_LIGHT)
		return (&((t_light *)obj->object)->origin_o_dir);
	return (NULL);
}

t_vec3	*get_obj_color(t_l_obj *obj)
{
	if (obj->type == SPHERE)
		return (&((t_sphere *)obj->object)->color);
	else if (obj->type == PLANE)
		return (&((t_plane *)obj->object)->color);
	else if (obj->type == CYLINDER)
		return (&((t_cylinder *)obj->object)->color);
	else if (obj->type == SPOT_LIGHT || obj->type == DIR_LIGHT)
		return (&((t_light *)obj->object)->color);
	return (NULL);
}

int	*get_obj_specular(t_l_obj *obj)
{
	if (obj->type == SPHERE)
		return (&((t_sphere *)obj->object)->specular);
	else if (obj->type == PLANE)
		return (&((t_plane *)obj->object)->specular);
	else if (obj->type == CYLINDER)
		return (&((t_cylinder *)obj->object)->specular);
	return (0);
}

double	*get_obj_reflection(t_l_obj *obj)
{
	if (obj->type == SPHERE)
		return (&((t_sphere *)obj->object)->reflect);
	else if (obj->type == PLANE)
		return (&((t_plane *)obj->object)->reflect);
	else if (obj->type == CYLINDER)
		return (&((t_cylinder *)obj->object)->reflect);
	return (0);
}
