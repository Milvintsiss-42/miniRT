/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:58:16 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 16:14:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// Equivalent to:
// ```
// return (vec3_magnitude(vec3_diff(point, cylinder.p_top_origin))
//		< cylinder.diameter / 2);
// ```
// but faster because we don't compute the square root.
static bool	is_point_on_top_cap(t_vec3 point, t_cylinder cylinder)
{
	return (vec3_pow2(vec3_diff(point, cylinder.p_top_origin))
		< cylinder.p_pow2_radius);
}

static bool	is_point_on_bottom_cap(t_vec3 point, t_cylinder cylinder)
{
	return (vec3_pow2(vec3_diff(point, cylinder.origin))
		< cylinder.p_pow2_radius);
}

// `t` is the height of the point on the cylinder.
// `c_pt_h` is the point on the cylinder's axis at the same height as `point`.
static t_vec3	get_cylinder_tube_normal_at_point(t_vec3 point,
	t_cylinder cylinder)
{
	t_vec3	normal;
	double	t;
	t_vec3	c_pt_h;

	t = vec3_dot_prdct(vec3_diff(point, cylinder.origin),
			cylinder.orientation);
	c_pt_h = vec3_sum(cylinder.origin,
			vec3_scal_prdct(cylinder.orientation, t));
	normal = vec3_normalize(vec3_diff(point, c_pt_h));
	return (normal);
}

t_vec3	get_cylinder_normal_at_point(t_vec3 point, t_cylinder cylinder)
{
	if (is_point_on_top_cap(point, cylinder))
		return (cylinder.orientation);
	else if (is_point_on_bottom_cap(point, cylinder))
		return (vec3_scal_prdct(cylinder.orientation, -1));
	else
		return (get_cylinder_tube_normal_at_point(point, cylinder));
}
