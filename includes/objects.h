/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:30:33 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/20 18:08:30 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "engine.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef enum e_obj_type
{
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
}	t_obj_type;

typedef struct s_l_object
{
	void				*object;
	t_obj_type			type;
	struct s_l_object	*next;
}	t_l_obj;

typedef struct s_amb_light
{
	double	brightness;
	int		color;
}	t_amb_light;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	origin;
	double	brightness;
	int		color;
}	t_light;

typedef struct s_sphere
{
	t_vec3	origin;
	double	radius;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	orientation;
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	origin;
	t_vec3	orientation;
	double	radius;
	double	height;
	int		color;
}	t_cylinder;

bool		l_obj_add_back(t_l_obj **l_obj, void *object, t_obj_type type);
t_l_obj		*l_obj_last(t_l_obj *l_obj);
void		free_object_list(t_l_obj *list);

#endif
