/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:13:55 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 21:55:09 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/// @brief Computes the intersections between a ray and a sphere.
/// @param ray The ray along which to compute the intersections.
/// @param sphere The sphere to intersect with.
/// @return Returns the distance between the origin of the ray and the
/// intersections.
/// Returns a t_quadratic struct containing the solved equation, t1 and t2 are
/// the distances of each intersection, t2 is the point where the ray enters the
/// sphere, t1 is the point where the ray exits the sphere.
/// If there is only one intersection (edge), t1 and t2 are equal.
/// If there is no intersection, t1 and t2 are set to inf.
t_quadratic	ray_sphere_intersections(t_ray ray, t_sphere sphere)
{
	t_quadratic	s;
	t_vec3		co;

	co = vec3_diff(ray.origin, sphere.origin);
	s.a = vec3_dot_prdct(ray.dir, ray.dir);
	s.b = 2 * vec3_dot_prdct(co, ray.dir);
	s.c = vec3_dot_prdct(co, co)
		- (sphere.diameter / 2) * (sphere.diameter / 2);
	solve_quadratic(&s);
	return (s);
}

// Returns int to avoid triggering the "use of bitwise operator with boolean
// operands" warning.
static int	is_closest_intersection_sphere(double t, t_ray ray,
	t_intersect *intersection)
{
	if (t >= ray.t_min && t <= ray.t_max && t < intersection->closest_t)
	{
		intersection->closest_t = t;
		return (true);
	}
	return (false);
}

void	closest_intersection_sphere(t_mrt *mrt, t_intersect *intersection,
	t_ray ray, t_l_obj *cur_sphere)
{
	t_quadratic	q;
	t_sphere	sphere;
	bool		have_intersection;

	if (cur_sphere->type == SPOT_LIGHT)
		sphere = sphere_from_light(*(t_light *)(cur_sphere->object));
	else
		sphere = *(t_sphere *)(cur_sphere->object);
	q = ray_sphere_intersections(ray, sphere);
	have_intersection = (is_closest_intersection_sphere(q.t1, ray, intersection)
			| is_closest_intersection_sphere(q.t2, ray, intersection));
	if (have_intersection
		&& (intersection->closest_t == q.t1 || intersection->closest_t == q.t2))
	{
		intersection->obj = cur_sphere;
		intersection->is_inside = (intersection->closest_t == q.t1);
		intersection->is_border = fabs(q.t1 - q.t2)
			< (((double)mrt->scene.camera.fov / 180)
				* sqrt(sphere.diameter)) / 2;
	}
}
