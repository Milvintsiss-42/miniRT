/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:01:42 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 20:12:23 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_sphere_to_scene_objects(t_mrt *mrt, t_parsing *parsing,
	t_sphere sphere)
{
	t_sphere	*sphere_ptr;

	sphere_ptr = malloc(sizeof(t_sphere));
	if (!sphere_ptr)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	*sphere_ptr = sphere;
	if (!l_obj_add_back(&mrt->scene.objects, sphere_ptr, SPHERE))
	{
		free(sphere_ptr);
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	}
}

void	add_sphere(t_mrt *mrt, t_parsing *parsing)
{
	t_sphere	sphere;

	if (ft_splitlen(parsing->s_line) != 4)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_vector(parsing->s_line[1], &sphere.origin))
		parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	if (!parse_double(parsing->s_line[2], &sphere.diameter))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (!parse_color(parsing->s_line[3], &sphere.color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
	add_sphere_to_scene_objects(mrt, parsing, sphere);
}
