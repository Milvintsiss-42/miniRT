/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 22:42:10 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 22:44:59 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_vec3	get_camera_ray_direction(t_mrt *mrt, int x, int y)
{
	t_vec3	base_direction;

	base_direction = canvas_to_viewport(mrt, x, y);
	return (rotate_vec3(base_direction,
			mrt->scene.camera.roll,
			mrt->scene.camera.yaw,
			mrt->scene.camera.pitch
		));
}

/// @brief Computes the reflection of a ray on a surface.
/// This use the following equation:
/// 2 * normal * (normal . ray) - ray
/// @param ray The ray to reflect.
/// @param normal The normal of the surface.
t_vec3	reflect_ray(t_vec3 ray, t_vec3 normal)
{
	return (vec3_diff(
			vec3_scal_prdct(
				vec3_scal_prdct(normal, 2.0),
				vec3_dot_prdct(normal, ray)),
			ray));
}
