/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:49 by ple-stra          #+#    #+#             */
/*   Updated: 2023/06/15 16:13:10 by ple-stra         ###   ########.fr       */
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

typedef struct s_mrt	t_mrt;

void		draw_frame(t_mrt *mrt);
void		draw_test_card_f(t_mrt *mrt);

double		compute_lighting(t_mrt mrt, t_vec3 point, t_vec3 normal);
int			apply_brightness_to_color(int color, double brightness);

#endif