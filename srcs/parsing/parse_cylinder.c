/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:01:42 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 20:18:52 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_cylinder_to_scene_objects(t_mrt *mrt, t_parsing *parsing,
	t_cylinder cylinder)
{
	t_cylinder	*cylinder_ptr;

	cylinder_ptr = malloc(sizeof(t_cylinder));
	if (!cylinder_ptr)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	*cylinder_ptr = cylinder;
	if (!l_obj_add_back(&mrt->scene.objects, cylinder_ptr, CYLINDER))
	{
		free(cylinder_ptr);
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	}
}

void	add_cylinder(t_mrt *mrt, t_parsing *parsing)
{
	t_cylinder	cylinder;

	if (ft_splitlen(parsing->s_line) != 6)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_vector(parsing->s_line[1], &cylinder.origin))
		parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	if (!parse_normalized_vector(parsing->s_line[2], &cylinder.orientation))
		parsing_error(mrt, *parsing, ERR_INVALID_NORM_VECTOR, true);
	if (!parse_double(parsing->s_line[3], &cylinder.diameter))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (!parse_double(parsing->s_line[4], &cylinder.height))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (!parse_color(parsing->s_line[5], &cylinder.color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
	add_cylinder_to_scene_objects(mrt, parsing, cylinder);
}
