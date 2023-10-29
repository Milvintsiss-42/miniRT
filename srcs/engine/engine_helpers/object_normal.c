/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:57:56 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/28 22:41:01 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_vec3	get_sphere_normal_at_point(t_vec3 point, t_sphere sphere)
{
	return (vec3_normalize(vec3_diff(point, sphere.origin)));
}

t_vec3	get_plane_normal_at_point(t_ray ray, t_plane plane)
{
	if (vec3_dot_prdct(plane.orientation, ray.dir) > 0)
		return (vec3_scal_prdct(plane.orientation, -1));
	return (plane.orientation);
}

t_vec3	get_object_normal_at_point(t_vec3 point, t_ray ray,
	t_intersect intersect)
{
	t_vec3	normal;

	normal = (t_vec3){0, 0, 0};
	if (intersect.obj->type == SPOT_LIGHT)
		normal = get_sphere_normal_at_point(point, sphere_from_light(
					*(t_light *)(intersect.obj->object)));
	else if (intersect.obj->type == SPHERE)
		normal = get_sphere_normal_at_point(point,
				*(t_sphere *)(intersect.obj->object));
	else if (intersect.obj->type == PLANE)
		normal = get_plane_normal_at_point(ray,
				*(t_plane *)(intersect.obj->object));
	else if (intersect.obj->type == CYLINDER)
		normal = get_cylinder_normal_at_point(point,
				*(t_cylinder *)(intersect.obj->object));
	if (intersect.is_inside)
		normal = vec3_scal_prdct(normal, -1);
	return (normal);
}
