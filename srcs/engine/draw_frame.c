/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2023/09/06 00:20:38 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

/// @brief Converts a pixel coordinate on the canvas to a viewport coordinate.
/// @param mrt
/// @param x
/// @param y
/// @return Returns a t_vec3 containing the viewport coordinates.
t_vec3	canvas_to_viewport(t_mrt *mrt, int x, int y)
{
	t_vec3	vp;

	vp.x = x * mrt->scene.viewport.w / mrt->mlx.win_width;
	vp.y = y * mrt->scene.viewport.h / mrt->mlx.win_height;
	vp.z = VP_DIST;
	return (vp);
}

/// @brief Computes the intersections between a ray and a sphere.
/// @param origin The origin of the ray.
/// @param dir The direction of the ray.
/// @param sphere The sphere to intersect with.
/// @return Returns the distance between the origin of the ray and the
/// intersections.
/// Returns a t_quadratic struct containing the solved equation, t1 and t2 are
/// the distances of each intersection.
/// If there is only one intersection, t1 and t2 are equal.
/// If there is no intersection, t1 and t2 are set to 1.0 / 0.0.
t_quadratic	intersect_ray_sphere(t_vec3 origin, t_vec3 dir, t_sphere sphere)
{
	t_quadratic	s;
	t_vec3		co;

	co = vec3_diff(origin, sphere.origin);
	s.a = vec3_dot_prdct(dir, dir);
	s.b = 2 * vec3_dot_prdct(co, dir);
	s.c = vec3_dot_prdct(co, co)
		- (sphere.diameter / 2) * (sphere.diameter / 2);
	s.discriminant = s.b * s.b - 4 * s.a * s.c;
	s.t1 = 1.0 / 0.0;
	s.t2 = 1.0 / 0.0;
	if (s.discriminant >= 0)
	{
		s.t1 = (-s.b + sqrt(s.discriminant)) / (2 * s.a);
		s.t2 = (-s.b - sqrt(s.discriminant)) / (2 * s.a);
	}
	return (s);
}

// See the function compute_lighting for more informations about the variables
// in the t_point struct.
int	compute_sphere_point_color(t_mrt mrt, t_vec3 origin, t_vec3 dir,
	t_sphere sphere, double closest_t)
{
	t_point	point;
	t_vec3	color;

	point.p = vec3_sum(origin, vec3_scal_prdct(dir, closest_t));
	point.n = vec3_normalize(vec3_diff(point.p, sphere.origin));
	point.v = vec3_scal_prdct(dir, -1);
	point.s = sphere.specular;
	compute_lighting(mrt, &point);
	color = vec3_scal_prdct(sphere.color, point.b);
	return (t_vec3_color_to_int(color));
}

int	trace_ray(t_mrt *mrt, t_vec3 origin, t_vec3 dir)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_l_obj		*obj_iter;
	t_quadratic	t;

	closest_t = 1.0 / 0.0;
	closest_sphere = NULL;
	obj_iter = mrt->scene.objects;
	while (obj_iter)
	{
		if (obj_iter->type == SPHERE)
		{
			t = intersect_ray_sphere(
					origin, dir, *(t_sphere *)(obj_iter->object));
			if (t.t1 >= T_MIN && t.t1 <= T_MAX && t.t1 < closest_t)
			{
				closest_t = t.t1;
				closest_sphere = obj_iter->object;
			}
			if (t.t2 >= T_MIN && t.t2 <= T_MAX && t.t2 < closest_t)
			{
				closest_t = t.t2;
				closest_sphere = obj_iter->object;
			}
		}
		obj_iter = obj_iter->next;
	}
	if (!closest_sphere)
		return (BACKGROUND_COLOR);
	return (compute_sphere_point_color(*mrt, origin, dir, *closest_sphere,
			closest_t));
}

void	draw_frame(t_mrt *mrt)
{
	int		x;
	int		y;
	t_vec3	dir;
	int		color;

	x = -mrt->mlx.win_width / 2 - 1;
	while (x < mrt->mlx.win_width / 2 + 1)
	{
		y = -mrt->mlx.win_height / 2 - 1;
		while (y < mrt->mlx.win_height / 2 + 1)
		{
			dir = canvas_to_viewport(mrt, x, y);
			color = trace_ray(mrt, mrt->scene.camera.origin, dir);
			put_pixel_on_img(mrt, x, y, color);
			y++;
		}
		x++;
		print_progress(x, -mrt->mlx.win_width / 2, mrt->mlx.win_width / 2);
	}
}
