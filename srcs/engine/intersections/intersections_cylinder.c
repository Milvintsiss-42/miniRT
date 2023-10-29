/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:34:02 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 21:54:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/// @brief Computes the intersection between a ray and a disk.
/// @param ray The ray along which to compute the intersection.
/// @param origin The origin of the disk.
/// @param orientation The orientation of the disk.
/// @param pow2_radius The squared radius of the disk.
/// @return Returns the distance between the origin of the ray and the
/// intersection.
/// Returns inf if there is no intersection.
double	ray_disk_intersection(t_ray ray, t_vec3 origin, t_vec3 orientation,
	double pow2_radius)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = vec3_dot_prdct(ray.dir, orientation);
	if (fabs(denom) < LOW_DBL)
		return (1.0 / 0.0);
	t = vec3_dot_prdct(vec3_diff(origin, ray.origin), orientation)
		/ denom;
	p = vec3_sum(ray.origin, vec3_scal_prdct(ray.dir, t));
	if (vec3_pow2(vec3_diff(p, origin)) > pow2_radius)
		return (1.0 / 0.0);
	return (t);
}

/// @brief Computes the intersections between a ray and a cylinder_tube.
/// @param ray The ray along which to compute the intersections.
/// @param cylinder The cylinder to intersect with.
/// @return Returns the distance between the origin of the ray and the
/// intersections.
/// Returns a t_quadratic struct containing the solved equation, t1 and t2 are
/// the distances of each intersection, t2 is the point where the ray enters the
/// cylinder, t1 is the point where the ray exits the cylinder.
/// If there is only one intersection (edge), t1 and t2 are equal.
/// If there is no intersection, t1 and t2 are set to inf.
t_quadratic	ray_cylinder_tube_intersections(t_ray ray, t_cylinder cylinder)
{
	t_quadratic	q;
	t_vec3		ra0;
	t_vec3		va;

	ra0 = vec3_cross_prdct(vec3_cross_prdct(cylinder.orientation,
				vec3_diff(ray.origin, cylinder.origin)), cylinder.orientation);
	va = vec3_cross_prdct(vec3_cross_prdct(cylinder.orientation, ray.dir),
			cylinder.orientation);
	q.a = vec3_pow2(va);
	q.b = 2 * vec3_dot_prdct(ra0, va);
	q.c = vec3_pow2(ra0) - cylinder.p_pow2_radius;
	solve_quadratic(&q);
	return (q);
}

// Returns int to avoid triggering the "use of bitwise operator with boolean
// operands" warning.
static int	is_closest_intersection_finite_tube(double t, t_ray ray,
	t_intersect *intersection, t_cylinder cylinder)
{
	t_vec3		p;

	p = vec3_sum(ray.origin, vec3_scal_prdct(ray.dir, t));
	if (t >= ray.t_min && t <= ray.t_max && t < intersection->closest_t
		&& vec3_dot_prdct(
			vec3_diff(p, cylinder.origin), cylinder.orientation) > 0
		&& vec3_dot_prdct(
			vec3_diff(p, cylinder.p_top_origin), cylinder.orientation) < 0)
	{
		intersection->closest_t = t;
		return (true);
	}
	return (false);
}

// Returns int to avoid triggering the "use of bitwise operator with boolean
// operands" warning.
static int	is_closest_intersection_disk(double t, t_ray ray,
	t_intersect *intersection)
{
	if (t >= ray.t_min && t <= ray.t_max
		&& t < intersection->closest_t)
	{
		intersection->closest_t = t;
		return (true);
	}
	return (false);
}

void	closest_intersection_cylinder(t_mrt *mrt, t_intersect *intersection,
	t_ray ray, t_l_obj *cur_cylinder)
{
	t_cylinder	cylinder;
	t_quadratic	q;
	t_tdisk		tdisk;
	bool		have_intersection;

	cylinder = *(t_cylinder *)(cur_cylinder->object);
	q = ray_cylinder_tube_intersections(ray, cylinder);
	tdisk.bottom = ray_disk_intersection(ray, cylinder.origin,
			cylinder.orientation, cylinder.p_pow2_radius);
	tdisk.top = ray_disk_intersection(ray, cylinder.p_top_origin,
			cylinder.orientation, cylinder.p_pow2_radius);
	have_intersection = (is_closest_intersection_finite_tube(q.t1, ray,
				intersection, cylinder)
			| is_closest_intersection_finite_tube(q.t2, ray, intersection,
				cylinder)
			| is_closest_intersection_disk(tdisk.bottom, ray, intersection)
			| is_closest_intersection_disk(tdisk.top, ray, intersection));
	if (have_intersection
		&& (intersection->closest_t == q.t1 || intersection->closest_t == q.t2))
		register_cylinder_tube_intersection(mrt, intersection, cur_cylinder, q);
	else if (have_intersection
		&& (intersection->closest_t == tdisk.bottom
			|| intersection->closest_t == tdisk.top))
		register_cylinder_disk_intersection(intersection, cur_cylinder, ray,
			tdisk);
}
