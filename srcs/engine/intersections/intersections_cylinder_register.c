/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder_register.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:20:17 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 20:32:35 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	register_cylinder_tube_intersection(t_mrt *mrt,
	t_intersect *intersection, t_l_obj *cur_cylinder, t_quadratic solv_q)
{
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)(cur_cylinder->object);
	intersection->obj = cur_cylinder;
	intersection->is_inside = (intersection->closest_t == solv_q.t1);
	intersection->is_border = (intersection->obj->is_selected
			&& fabs(solv_q.t1 - solv_q.t2)
			< (((double)mrt->scene.camera.fov / 180)
				* sqrt(cylinder.diameter)) / 2);
}

static bool	is_disk_border(t_ray ray, t_vec3 disk_origin, double t,
	double pow2_radius)
{
	return (pow(
			vec3_pow2(vec3_diff(
					vec3_sum(ray.origin, vec3_scal_prdct(ray.dir, t)),
					disk_origin))
			- pow2_radius,
			2)
		< pow2_radius / 100);
}

void	register_cylinder_disk_intersection(t_intersect *intersection,
	t_l_obj *cur_cylinder, t_ray ray, t_tdisk tdisk)
{
	t_cylinder	cylinder;

	cylinder = *(t_cylinder *)(cur_cylinder->object);
	intersection->obj = cur_cylinder;
	if (intersection->closest_t == tdisk.bottom)
	{
		intersection->is_inside
			= vec3_dot_prdct(cylinder.orientation, ray.dir) <= 0;
		intersection->is_border = (intersection->obj->is_selected
				&& is_disk_border(ray, cylinder.origin, tdisk.bottom,
					cylinder.p_pow2_radius));
	}
	else if (intersection->closest_t == tdisk.top)
	{
		intersection->is_inside
			= vec3_dot_prdct(cylinder.orientation, ray.dir) > 0;
		intersection->is_border = (intersection->obj->is_selected
				&& is_disk_border(ray, cylinder.p_top_origin, tdisk.top,
					cylinder.p_pow2_radius));
	}
}
