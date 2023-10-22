/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:30:33 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 08:46:01 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "engine.h"
# include "math_helpers.h"

typedef enum e_obj_type
{
	SPOT_LIGHT,
	DIR_LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_obj_type;

typedef struct s_l_object
{
	void				*object;
	t_obj_type			type;
	struct s_l_object	*next;
	bool				is_selected;
}	t_l_obj;

typedef struct s_amb_light
{
	double	brightness;
	t_vec3	color;
}	t_amb_light;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	start_dir;
	int		fov;
	double	yaw;
	double	pitch;
	double	roll;
}	t_camera;

typedef struct s_light
{
	t_vec3	origin_o_dir;
	double	brightness;
	t_vec3	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3	origin;
	double	diameter;
	t_vec3	color;
	int		specular;
	double	reflect;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	orientation;
	t_vec3	color;
	int		specular;
	double	reflect;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	origin;
	t_vec3	orientation;
	double	diameter;
	double	height;
	t_vec3	color;
	int		specular;
	double	reflect;
}	t_cylinder;

bool		l_obj_add_back(t_l_obj **l_obj, void *object, t_obj_type type);
t_l_obj		*l_obj_last(t_l_obj *l_obj);
void		free_object_list(t_l_obj *list);

t_vec3		*get_obj_origin(t_l_obj *obj);
t_vec3		*get_obj_orientation(t_l_obj *obj);
t_vec3		*get_obj_color(t_l_obj *obj);
int			*get_obj_specular(t_l_obj *obj);
double		*get_obj_reflection(t_l_obj *obj);

#endif
