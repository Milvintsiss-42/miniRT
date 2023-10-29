/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:11:09 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 21:56:17 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// Computes the intersections with lights represented as spheres. This is used
// to visualize the lights when FLAG_LIGHT_V is active.
static void	intersection_light_spheres(t_mrt *mrt, t_intersect *intersection,
	t_ray ray)
{
	t_l_obj		*obj_iter;

	if (!ft_checkflag(mrt->event_mode.flags, FLAG_LIGHT_V))
		return ;
	obj_iter = mrt->scene.lights;
	while (obj_iter)
	{
		if (obj_iter->type == SPOT_LIGHT)
			closest_intersection_sphere(mrt, intersection, ray, obj_iter);
		obj_iter = obj_iter->next;
	}
}

/// @brief Computes the closest intersection between a ray and all the objects
/// in the scene.
/// @param mrt 
/// @param ray The ray along which to compute the intersections.
/// @return Returns a t_intersect struct containing the distance of the closest
/// intersection and the object that was intersected.
/// If there is no intersection, the distance is set to inf and the object to
/// NULL.
t_intersect	closest_intersection(t_mrt *mrt, t_ray ray)
{
	t_intersect	intersection;
	t_l_obj		*obj_iter;

	intersection.closest_t = __DBL_MAX__;
	intersection.obj = NULL;
	intersection.is_border = false;
	obj_iter = mrt->scene.objects;
	while (obj_iter)
	{
		if (obj_iter->type == SPHERE)
			closest_intersection_sphere(mrt, &intersection, ray, obj_iter);
		else if (obj_iter->type == PLANE)
			closest_intersection_plane(&intersection, ray, obj_iter);
		else if (obj_iter->type == CYLINDER)
			closest_intersection_cylinder(mrt, &intersection, ray, obj_iter);
		obj_iter = obj_iter->next;
	}
	intersection_light_spheres(mrt, &intersection, ray);
	return (intersection);
}
