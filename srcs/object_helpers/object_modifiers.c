/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_modifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:34:30 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/25 12:02:44 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	translate_object(t_mrt *mrt, t_l_obj *obj, int direction)
{
	t_vec3	*origin;

	origin = get_obj_origin(obj);
	if (!origin)
		return ;
	*origin = (t_vec3){
		origin->x + (direction * TRANSLATE_SPEED * (mrt->event_mode.axis == X)),
		origin->y + (direction * TRANSLATE_SPEED * (mrt->event_mode.axis == Y)),
		origin->z + (direction * TRANSLATE_SPEED * (mrt->event_mode.axis == Z))
	};
}

void	resize_object(t_mrt *mrt, t_l_obj *obj, int direction)
{
	if (obj->type == SPHERE)
		((t_sphere *)obj->object)->diameter += direction * RESIZE_SPEED;
	else if (obj->type == CYLINDER)
	{
		if (ft_checkflag(mrt->event_mode.flags, FLAG_DIAMETER))
			((t_cylinder *)obj->object)->diameter += direction * RESIZE_SPEED;
		if (ft_checkflag(mrt->event_mode.flags, FLAG_HEIGHT))
			((t_cylinder *)obj->object)->height += direction * RESIZE_SPEED;
	}
	else if (obj->type == SPOT_LIGHT || obj->type == DIR_LIGHT)
	{
		((t_light *)obj->object)->brightness
			+= direction * LIGHT_INTENSITY_SPEED;
		((t_light *)obj->object)->brightness = ft_max_d(
				0.0, ft_min_d(((t_light *)obj->object)->brightness, 1.0));
	}
}

void	rotate_object(t_mrt *mrt, t_l_obj *obj, int direction)
{
	t_vec3	*orientation;

	orientation = get_obj_orientation(obj);
	if (!orientation)
		return ;
	*orientation = rotate_vec3(*orientation,
			direction * ROTATE_SPEED * (mrt->event_mode.axis == X),
			direction * ROTATE_SPEED * (mrt->event_mode.axis == Y),
			direction * ROTATE_SPEED * (mrt->event_mode.axis == Z));
}

void	update_amb_light_intensity(t_mrt *mrt, int direction)
{
	mrt->scene.amb_light.brightness += direction * LIGHT_INTENSITY_SPEED;
	mrt->scene.amb_light.brightness = ft_max_d(
			0.0, ft_min_d(mrt->scene.amb_light.brightness, 1.0));
}
