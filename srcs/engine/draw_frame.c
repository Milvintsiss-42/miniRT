/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/23 07:42:47 by ple-stra         ###   ########.fr       */
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

/// @brief Computes the reflection of a ray on a surface.
/// This use the following equation:
/// 2 * normal * (normal . ray) - ray
/// @param ray The ray to reflect.
/// @param normal The normal of the surface.
t_vec3	reflect_ray(t_vec3 ray, t_vec3 normal)
{
	return (vec3_diff(
			vec3_scal_prdct(
				vec3_scal_prdct(normal, 2.0),
				vec3_dot_prdct(normal, ray)),
			ray));
}

/// @brief Computes the intersections between a ray and a sphere.
/// @param ray The ray along which to compute the intersections.
/// @param sphere The sphere to intersect with.
/// @return Returns the distance between the origin of the ray and the
/// intersections.
/// Returns a t_quadratic struct containing the solved equation, t1 and t2 are
/// the distances of each intersection, t2 is the point where the ray enters the
/// sphere, t1 is the point where the ray exits the sphere.
/// If there is only one intersection, t1 and t2 are equal.
/// If there is no intersection, t1 and t2 are set to 1.0 / 0.0.
t_quadratic	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_quadratic	s;
	t_vec3		co;

	co = vec3_diff(ray.origin, sphere.origin);
	s.a = vec3_dot_prdct(ray.dir, ray.dir);
	s.b = 2 * vec3_dot_prdct(co, ray.dir);
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

void	closest_intersection_sphere(t_mrt *mrt, t_intersect *intersection,
	t_ray ray, t_l_obj *cur_sphere, double t_min, double t_max)
{
	t_quadratic	q;
	t_sphere	sphere;

	if (cur_sphere->type == SPOT_LIGHT)
		sphere = sphere_from_light(*(t_light *)(cur_sphere->object));
	else
		sphere = *(t_sphere *)(cur_sphere->object);
	q = intersect_ray_sphere(ray, sphere);
	if (q.t1 >= t_min && q.t1 <= t_max && q.t1 < intersection->closest_t)
		intersection->closest_t = q.t1;
	if (q.t2 >= t_min && q.t2 <= t_max && q.t2 < intersection->closest_t)
		intersection->closest_t = q.t2;
	if (intersection->closest_t == q.t1 || intersection->closest_t == q.t2)
	{
		intersection->obj = cur_sphere;
		intersection->is_inside = (intersection->closest_t == q.t1);
		intersection->is_border = fabs(q.t1 - q.t2)
			< (((double)mrt->scene.camera.fov / 180)
				* sqrt(sphere.diameter)) / 2;
	}
}

void	closest_intersection_plane(t_mrt *mrt, t_intersect *intersection,
	t_ray ray, t_l_obj *cur_plane, double t_min, double t_max)
{
	t_plane		plane;
	double		denom;
	double		t;

	plane = *(t_plane *)(cur_plane->object);
	denom = vec3_dot_prdct(ray.dir, plane.orientation);
	if (fabs(denom) < LOW_DBL)
		return ;
	t = vec3_dot_prdct(vec3_diff(plane.origin, ray.origin), plane.orientation)
		/ denom;
	if (t >= t_min && t <= t_max && t < intersection->closest_t)
	{
		intersection->closest_t = t;
		intersection->obj = cur_plane;
		intersection->is_inside = false;
		intersection->is_border = false;
	}
}

t_intersect	closest_intersection(t_mrt *mrt, t_ray ray,
	double t_min, double t_max)
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
			closest_intersection_sphere(mrt, &intersection, ray, obj_iter,
				t_min, t_max);
		else if (obj_iter->type == PLANE)
			closest_intersection_plane(mrt, &intersection, ray, obj_iter,
				t_min, t_max);
		obj_iter = obj_iter->next;
	}
	if (ft_checkflag(mrt->event_mode.flags, FLAG_LIGHT_V))
	{
		obj_iter = mrt->scene.lights;
		while (obj_iter)
		{
			if (obj_iter->type == SPOT_LIGHT)
				closest_intersection_sphere(mrt, &intersection, ray, obj_iter,
					t_min, t_max);
			obj_iter = obj_iter->next;
		}
	}
	return (intersection);
}

t_vec3	get_object_normal_at_point(t_ray ray, t_intersect intersect,
	t_vec3 point_origin)
{
	t_vec3	normal;

	normal = (t_vec3){0, 0, 0};
	if (intersect.obj->type == SPHERE || intersect.obj->type == SPOT_LIGHT)
		normal = vec3_normalize(
				vec3_diff(point_origin, *get_obj_origin(intersect.obj)));
	else if (intersect.obj->type == PLANE)
	{
		normal = *get_obj_orientation(intersect.obj);
		if (vec3_dot_prdct(normal, ray.dir) > 0)
			normal = vec3_scal_prdct(normal, -1);
	}
	if (intersect.is_inside)
		normal = vec3_scal_prdct(normal, -1);
	return (normal);
}

// See the function compute_lighting for more informations about the variables
// in the t_point struct.
t_point	compute_point_color(t_mrt *mrt, t_ray ray, t_intersect intersect)
{
	t_point	point;
	t_vec3	color;

	point.p = vec3_sum(ray.origin,
			vec3_scal_prdct(ray.dir, intersect.closest_t));
	point.n = get_object_normal_at_point(ray, intersect, point.p);
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

int	trace_ray(t_mrt *mrt, t_ray ray,
	double t_min, double t_max, int reflect_rec_depth)
{
	t_intersect	clst_intersect;
	t_point		point;
	int			reflected_color;
	double		reflection;

	clst_intersect = closest_intersection(mrt, ray, t_min, t_max);
	if (!clst_intersect.obj)
		return (BACKGROUND_COLOR);
	point = compute_point_color(mrt, ray, clst_intersect);
	if (clst_intersect.obj->type != SPOT_LIGHT)
		reflection = *get_obj_reflection(clst_intersect.obj);
	else
		reflection = 0.0;
	if (clst_intersect.obj->is_selected
		&& (clst_intersect.is_border || (clst_intersect.obj->type != SPHERE
				&& clst_intersect.obj->type != SPOT_LIGHT)))
		return (RED);
	if (reflect_rec_depth <= 0 || reflection <= 0.0)
		return (point.color);
	reflected_color = trace_ray(mrt,
			(t_ray){point.p, reflect_ray(point.v, point.n)},
			LOW_DBL, __DBL_MAX__, reflect_rec_depth - 1);
	return (blend_colors(point.color, reflected_color, 1 - reflection));
}

t_vec3	get_ray_direction(t_mrt *mrt, int x, int y)
{
	t_vec3	base_direction;

	base_direction = canvas_to_viewport(mrt, x, y);
	return (rotate_vec3(base_direction,
			mrt->scene.camera.roll,
			mrt->scene.camera.yaw,
			mrt->scene.camera.pitch
		));
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

	set_viewport_dimensions(mrt);
	x = 0;
	while (x < mrt->mlx.win_width)
	{
		y = 0;
		while (y < mrt->mlx.win_height)
		{
			ray_dir = get_ray_direction(mrt, x, y);
			color = trace_ray(mrt, (t_ray){mrt->scene.camera.origin, ray_dir},
					1.0, __DBL_MAX__, REFLECT_REC_DEPTH);
			put_pixel_on_img(mrt, x, y, color);
			y++;
		}
		x++;
	}
}
