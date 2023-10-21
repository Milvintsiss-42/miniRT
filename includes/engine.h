/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:49 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/21 04:14:54 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "common.h"
# include "objects.h"

# define REFLECT_REC_DEPTH	3

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
	bool	is_border;
}	t_intersect;

typedef struct s_mrt	t_mrt;

void		draw_frame(t_mrt *mrt);
t_vec3		canvas_to_viewport(t_mrt *mrt, int x, int y);
t_intersect	closest_intersection(t_mrt *mrt, t_vec3 origin, t_vec3 dir,
				double t_min, double t_max);
t_vec3		reflect_ray(t_vec3 ray, t_vec3 normal);
void		draw_test_card_f(t_mrt *mrt);

void		compute_lighting(t_mrt *mrt, t_point *p);
int			t_vec3_color_to_int(t_vec3 color);
t_vec3		int_color_to_t_vec3(int color);
int			blend_colors(int color1, int color2, double ratio);

#endif