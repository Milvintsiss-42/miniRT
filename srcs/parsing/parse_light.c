/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 20:00:52 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_ambiant_light(t_mrt *mrt, t_parsing *parsing)
{
	t_amb_light	*amb_light;

	amb_light = &mrt->scene.amb_light;
	if (amb_light->brightness != -1)
		parsing_error(mrt, *parsing, ERR_MULTIPLE_AMBIANT, true);
	if (ft_splitlen(parsing->s_line) != 3)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_double(parsing->s_line[1], &amb_light->brightness))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (amb_light->brightness < 0 || amb_light->brightness > 1)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
	if (!parse_color(parsing->s_line[2], &amb_light->color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
}

static void	add_light_to_scene_lights(t_mrt *mrt, t_parsing *parsing,
	t_light light)
{
	t_light	*light_ptr;

	light_ptr = malloc(sizeof(t_light));
	if (!light_ptr)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	*light_ptr = light;
	if (!l_obj_add_back(&mrt->scene.lights, light_ptr, LIGHT))
	{
		free(light_ptr);
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	}
}

void	add_light(t_mrt *mrt, t_parsing *parsing)
{
	t_light	light;

	if (ft_splitlen(parsing->s_line) != 4)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_vector(parsing->s_line[1], &light.origin))
		parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	if (!parse_double(parsing->s_line[2], &light.brightness))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (light.brightness < 0 || light.brightness > 1)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
	if (!parse_color(parsing->s_line[3], &light.color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
	add_light_to_scene_lights(mrt, parsing, light);
}
