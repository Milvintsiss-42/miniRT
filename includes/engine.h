/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:49 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 00:51:45 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "common.h"
# include "objects.h"

# define REFLECT_REC_DEPTH	3

# define LOW_DBL			0.0000001

typedef struct s_viewport
{
	double	w;
	double	h;
	double	dist;
}	t_viewport;

typedef struct s_scene
{
	t_viewport	viewport;
	t_l_obj		*objects;
	t_l_obj		*lights;
	t_amb_light	amb_light;
	t_camera	camera;
}	t_scene;

// This struct is used to store results of calculations during the computing of
// the brightness of a point. For more informations about the variables, see
// the function compute_lighting.
typedef struct s_point
{
	t_vec3	p;
	t_vec3	n;
	t_vec3	v;
	int		s;
	t_vec3	l;
	t_vec3	r;
	t_vec3	b;
	int		color;
}	t_point;

typedef struct s_intersect
{
	t_l_obj	*obj;
	double	closest_t;
	bool	is_inside;
	bool	is_border;
}	t_intersect;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	double	t_min;
	double	t_max;
}	t_ray;

typedef struct s_tdisk
{
	double	top;
	double	bottom;
}	t_tdisk;

typedef struct s_mrt	t_mrt;

void		draw_frame(t_mrt *mrt);
void		draw_test_card_f(t_mrt *mrt);

void		compute_lighting(t_mrt *mrt, t_point *p);

t_sphere	sphere_from_light(t_light light);

// ---engine_helpers---
// color_helpers
int			t_vec3_color_to_int(t_vec3 color);
t_vec3		int_color_to_t_vec3(int color);
int			blend_colors(int color1, int color2, double ratio);
t_vec3		brightness_color_wise(double brightness, t_vec3 color);
// objects normals
t_vec3		get_object_normal_at_point(t_vec3 point, t_ray ray,
				t_intersect intersect);
t_vec3		get_sphere_normal_at_point(t_vec3 point, t_sphere sphere);
t_vec3		get_plane_normal_at_point(t_ray ray, t_plane plane);
t_vec3		get_cylinder_normal_at_point(t_vec3 point, t_cylinder cyl);
// precompute
void		precompute_basics(t_mrt	*mrt);
void		precompute_sphere_basics(t_sphere *sphere);
void		precompute_cylinder_basics(t_cylinder *cylinder);
// ray
t_vec3		get_camera_ray_direction(t_mrt *mrt, int x, int y);
t_vec3		reflect_ray(t_vec3 ray, t_vec3 normal);
// viewport
void		set_viewport_dimensions(t_mrt *mrt);
t_vec3		canvas_to_viewport(t_mrt *mrt, int x, int y);

// ---intersections---
t_intersect	closest_intersection(t_mrt *mrt, t_ray ray);
// sphere
void		closest_intersection_sphere(t_mrt *mrt, t_intersect *intersection,
				t_ray ray, t_l_obj *cur_sphere);
t_quadratic	ray_sphere_intersections(t_ray ray, t_sphere sphere);
// plane
void		closest_intersection_plane(t_intersect *intersection,
				t_ray ray, t_l_obj *cur_plane);
double		ray_plane_intersection(t_ray ray, t_plane plane);
// cylinder
void		closest_intersection_cylinder(t_mrt *mrt, t_intersect *intersection,
				t_ray ray, t_l_obj *cur_cylinder);
double		ray_disk_intersection(t_ray ray, t_vec3 origin, t_vec3 orientation,
				double pow2_radius);
t_quadratic	ray_cylinder_tube_intersections(t_ray ray, t_cylinder cylinder);
void		register_cylinder_tube_intersection(t_mrt *mrt,
				t_intersect *intersection, t_l_obj *cur_cylinder,
				t_quadratic solv_q);
void		register_cylinder_disk_intersection(t_intersect *intersection,
				t_l_obj *cur_cylinder, t_ray ray, t_tdisk tdisk);

#endif
