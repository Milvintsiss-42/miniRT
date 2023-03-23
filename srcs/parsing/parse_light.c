/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:51:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 17:34:51 by ple-stra         ###   ########.fr       */
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
