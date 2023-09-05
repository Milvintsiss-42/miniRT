/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:49 by ple-stra          #+#    #+#             */
/*   Updated: 2023/09/06 00:10:17 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "common.h"
# include "objects.h"

# define DOUBLE_MAX()	1.0 / 0.0

# define VP_DIST	1
# define T_MIN		1.0
# define T_MAX		DOUBLE_MAX()

typedef struct s_viewport
{
	double	w;
	double	h;
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
	double	b;
}	t_point;

typedef struct s_mrt	t_mrt;

void		draw_frame(t_mrt *mrt);
void		draw_test_card_f(t_mrt *mrt);

void		compute_lighting(t_mrt mrt, t_point *p);
int			t_vec3_color_to_int(t_vec3 color);

#endif