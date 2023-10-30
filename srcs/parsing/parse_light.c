/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 14:56:42 by ple-stra         ###   ########.fr       */
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
	if (!IS_BONUS)
		amb_light->color = (t_vec3){255, 255, 255};
}

static void	add_light_to_scene_lights(t_mrt *mrt, t_parsing *parsing,
	t_light light, bool is_directional)
{
	t_light		*light_ptr;
	t_obj_type	type;

	if (is_directional)
		type = DIR_LIGHT;
	else
		type = SPOT_LIGHT;
	light_ptr = malloc(sizeof(t_light));
	if (!light_ptr)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	*light_ptr = light;
	if (!l_obj_add_back(&mrt->scene.lights, light_ptr, type))
	{
		free(light_ptr);
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	}
}

void	add_light(t_mrt *mrt, t_parsing *parsing, bool is_directional)
{
	t_light	light;

	if (!IS_BONUS && mrt->scene.lights != 0)
		parsing_error(mrt, *parsing, ERR_MULTIPLE_LIGHTS, true);
	if (ft_splitlen(parsing->s_line) != 4)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (is_directional)
	{
		if (!parse_normalized_vector(parsing->s_line[1], &light.origin_o_dir))
			parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	}
	else
	{
		if (!parse_vector(parsing->s_line[1], &light.origin_o_dir))
			parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	}
	if (!parse_double(parsing->s_line[2], &light.brightness))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (light.brightness < 0 || light.brightness > 1)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
	if (!parse_color(parsing->s_line[3], &light.color))
		parsing_error(mrt, *parsing, ERR_INVALID_COLOR, true);
	if (!IS_BONUS)
		light.color = (t_vec3){255, 255, 255};
	add_light_to_scene_lights(mrt, parsing, light, is_directional);
}
