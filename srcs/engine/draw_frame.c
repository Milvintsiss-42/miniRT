/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 00:24:59 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

t_sphere	sphere_from_light(t_light light)
{
	t_sphere	sphere;

	sphere.origin = light.origin_o_dir;
	sphere.diameter = 0.5;
	sphere.color = int_color_to_t_vec3(WHITE);
	sphere.specular = -1;
	sphere.reflect = 0.0;
	return (sphere);
}

/// @brief Converts a pixel coordinate on the canvas to a viewport coordinate.
/// @param mrt
/// @param x
/// @param y
/// @return Returns a t_vec3 containing the viewport coordinates.
t_vec3	canvas_to_viewport(t_mrt *mrt, int x, int y)
{
	t_vec3	vp;

	x -= mrt->mlx.win_width / 2;
	y = mrt->mlx.win_height / 2 - y;
	vp.x = x * mrt->scene.viewport.w / mrt->mlx.win_width;
	vp.y = y * mrt->scene.viewport.h / mrt->mlx.win_height;
	vp.z = mrt->scene.viewport.dist;
	return (vp);
}

// See the function compute_lighting for more informations about the variables
// in the t_point struct.
t_point	compute_point_color(t_mrt *mrt, t_ray ray, t_intersect intersect)
{
	t_point	point;
	t_vec3	color;

	point.p = vec3_sum(ray.origin,
			vec3_scal_prdct(ray.dir, intersect.closest_t));
	point.n = get_object_normal_at_point(point.p, ray, intersect);
	point.v = vec3_scal_prdct(ray.dir, -1);
	if (intersect.obj->type != SPOT_LIGHT)
		point.s = *get_obj_specular(intersect.obj);
	else
		point.s = -1;
	compute_lighting(mrt, &point);
	color = *get_obj_color(intersect.obj);
	if (intersect.obj->type == SPOT_LIGHT)
		color = int_color_to_t_vec3(WHITE);
	color.x *= point.b.x;
	color.y *= point.b.y;
	color.z *= point.b.z;
	point.color = t_vec3_color_to_int(color);
	return (point);
}

int	trace_ray(t_mrt *mrt, t_ray ray, int reflect_rec_depth)
{
	t_intersect	clst_intersect;
	t_point		point;
	int			reflected_color;
	double		reflection;

	clst_intersect = closest_intersection(mrt, ray);
	if (!clst_intersect.obj)
		return (BACKGROUND_COLOR);
	point = compute_point_color(mrt, ray, clst_intersect);
	if (clst_intersect.obj->type != SPOT_LIGHT)
		reflection = *get_obj_reflection(clst_intersect.obj);
	else
		reflection = 0.0;
	if (clst_intersect.obj->is_selected
		&& (clst_intersect.is_border || (clst_intersect.obj->type != SPHERE
				&& clst_intersect.obj->type != CYLINDER
				&& clst_intersect.obj->type != SPOT_LIGHT)))
		return (RED);
	if (reflect_rec_depth <= 0 || reflection <= 0.0)
		return (point.color);
	reflected_color = trace_ray(mrt,
			(t_ray){point.p, reflect_ray(point.v, point.n), LOW_DBL,
			__DBL_MAX__},
			reflect_rec_depth - 1);
	return (blend_colors(point.color, reflected_color, 1 - reflection));
}

static void	set_viewport_dimensions(t_mrt *mrt)
{
	mrt->scene.viewport.w = 1.0;
	mrt->scene.viewport.h = 1.0;
	if (mrt->mlx.win_width >= mrt->mlx.win_height)
	{
		mrt->scene.viewport.w
			= mrt->scene.viewport.w * mrt->mlx.win_width / mrt->mlx.win_height;
		mrt->scene.viewport.dist = (mrt->scene.viewport.w / 2.0)
			/ tan(deg_to_rad(mrt->scene.camera.fov / 2.0));
	}
	else
	{
		mrt->scene.viewport.h
			= mrt->scene.viewport.h * mrt->mlx.win_height / mrt->mlx.win_width;
		mrt->scene.viewport.dist = (mrt->scene.viewport.h / 2.0)
			/ tan(deg_to_rad(mrt->scene.camera.fov / 2.0));
	}
}

void	draw_frame(t_mrt *mrt)
{
	int		x;
	int		y;
	t_vec3	ray_dir;
	int		color;
	int		reflect_rec_depth;

	reflect_rec_depth = REFLECT_REC_DEPTH
		* ft_checkflag(mrt->event_mode.flags, FLAG_REFLECT);
	set_viewport_dimensions(mrt);
	precompute_basics(mrt);
	x = 0;
	while (x < mrt->mlx.win_width)
	{
		y = 0;
		while (y < mrt->mlx.win_height)
		{
			ray_dir = get_camera_ray_direction(mrt, x, y);
			color = trace_ray(mrt, (t_ray){mrt->scene.camera.origin, ray_dir,
					1.0, __DBL_MAX__},
					reflect_rec_depth);
			put_pixel_on_img(mrt, x, y, color);
			y++;
		}
		x++;
	}
}
