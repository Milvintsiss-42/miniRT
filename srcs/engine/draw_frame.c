/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2025/01/28 03:48:11 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

// See the function compute_lighting for more informations about the variables
// in the t_point struct.
static t_point	compute_point_color(t_mrt *mrt, t_ray ray,
	t_intersect intersect)
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

static int	trace_ray(t_mrt *mrt, t_ray ray, int reflect_rec_depth)
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

static int	try_fade_pixel(t_mrt *mrt, int x, int y)
{
	int	fade_res;
	int	ref_x;
	int	ref_y;

	fade_res = mrt->img.fade_resolution;
	if (x % fade_res != 0 || y % fade_res != 0)
	{
		ref_x = x - (x % fade_res);
		ref_y = y - (y % fade_res);
		return (get_color_of_pixel_on_img(mrt, mrt->img.future, ref_x, ref_y));
	}
	if (fade_res < FADE_MIN_RES && x % (fade_res + 1) == 0
		&& y % (fade_res + 1) == 0)
		return (get_color_of_pixel_on_img(mrt, mrt->img.current, x, y));
	return (-1);
}

static int	compute_color_of_pixel(t_mrt *mrt, int x, int y,
	int reflect_rec_depth)
{
	int	faded_pixel;

	if (FADE_MIN_RES > 1)
	{
		faded_pixel = try_fade_pixel(mrt, x, y);
		if (faded_pixel >= 0)
			return (faded_pixel);
	}
	return (trace_ray(mrt,
			(t_ray){mrt->scene.camera.origin,
			get_camera_ray_direction(mrt, x, y),
			1.0, __DBL_MAX__},
		reflect_rec_depth));
}

void	draw_frame(t_mrt *mrt)
{
	int		x;
	int		y;
	int		pixel_color;
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
			pixel_color = compute_color_of_pixel(mrt, x, y, reflect_rec_depth);
			put_pixel_on_img(mrt, x, y, pixel_color);
			y++;
		}
		x++;
	}
	mrt->img.fade_resolution--;
}
