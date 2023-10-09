/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:01:42 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/09 08:30:01 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_plane_to_scene_objects(t_mrt *mrt, t_parsing *parsing,
	t_plane plane)
{
	t_plane	*plane_ptr;

	plane_ptr = malloc(sizeof(t_plane));
	if (!plane_ptr)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	*plane_ptr = plane;
	if (!l_obj_add_back(&mrt->scene.objects, plane_ptr, PLANE))
	{
		free(plane_ptr);
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	}
}

void	add_plane(t_mrt *mrt, t_parsing *parsing)
{
	t_plane	plane;

	if (ft_splitlen(parsing->s_line) != 6)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_vector(parsing->s_line[1], &plane.origin))
		parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	if (!parse_normalized_vector(parsing->s_line[2], &plane.orientation))
		parsing_error(mrt, *parsing, ERR_INVALID_NORM_VECTOR, true);
	if (!parse_color(parsing->s_line[3], &plane.color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
	if (!parse_int(parsing->s_line[4], &plane.specular))
		parsing_error(mrt, *parsing, ERR_INVALID_INT, true);
	if (plane.specular < -1)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
	if (!parse_double(parsing->s_line[5], &plane.reflect))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (plane.reflect < 0.0 || plane.reflect > 1.0)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
	add_plane_to_scene_objects(mrt, parsing, plane);
}
