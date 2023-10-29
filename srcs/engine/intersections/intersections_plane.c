/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:22:47 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 21:54:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/// @brief Computes the intersection between a ray and a plane.
/// @param ray The ray along which to compute the intersection.
/// @param plane The plane to intersect with.
/// @return Returns the distance between the origin of the ray and the
/// intersection.
/// Returns inf if there is no intersection.
double	ray_plane_intersection(t_ray ray, t_plane plane)
{
	double	denom;
	double	t;

	denom = vec3_dot_prdct(ray.dir, plane.orientation);
	if (fabs(denom) < LOW_DBL)
		return (1.0 / 0.0);
	t = vec3_dot_prdct(vec3_diff(plane.origin, ray.origin), plane.orientation)
		/ denom;
	return (t);
}

void	closest_intersection_plane(t_intersect *intersection, t_ray ray,
	t_l_obj *cur_plane)
{
	double	t;

	t = ray_plane_intersection(ray, *(t_plane *)(cur_plane->object));
	if (t >= ray.t_min && t <= ray.t_max && t < intersection->closest_t)
	{
		intersection->closest_t = t;
		intersection->obj = cur_plane;
		intersection->is_inside = false;
		intersection->is_border = false;
	}
}
