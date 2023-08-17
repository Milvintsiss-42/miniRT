/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:20:54 by ple-stra          #+#    #+#             */
/*   Updated: 2023/08/17 03:59:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/// @brief Computes the brightness of a point, based on the ambient light and
/// the lights in the scene.
/// @param mrt
/// @param point
/// @param normal The direction of the normal of the object at the point.
/// @return Returns the brightness of the point.
double	compute_lighting(t_mrt mrt, t_vec3 point, t_vec3 normal)
{
	t_l_obj	*lights;
	double	brightness;
	t_vec3	light_dir;

	lights = mrt.scene.lights;
	brightness = mrt.scene.amb_light.brightness;
	while (lights)
	{
		if (lights->type == SPOT_LIGHT || lights->type == DIR_LIGHT)
		{
			if (lights->type == SPOT_LIGHT)
				light_dir = vec3_diff(
						((t_light *)(lights->object))->origin_o_dir, point);
			else if (lights->type == DIR_LIGHT)
				light_dir = ((t_light *)(lights->object))->origin_o_dir;
			if (vec3_dot_prdct(normal, light_dir) > 0)
				brightness += ((t_light *)(lights->object))->brightness
					* vec3_dot_prdct(normal, light_dir)
					/ (vec3_magnitude(normal) * vec3_magnitude(light_dir));
		}
		lights = lights->next;
	}
	return (ft_min_d(brightness, 1.0));
}
