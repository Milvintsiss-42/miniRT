/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:45:00 by ple-stra          #+#    #+#             */
/*   Updated: 2023/06/15 16:27:00 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// We use t_vec3 to store colors, so x corresponds to red, y to green
// and z to blue.
bool	parse_color(char *str, t_vec3 *color_ret)
{
	char	**s_str;

	s_str = ft_split(str, ',');
	if (!s_str)
		return (false);
	if (ft_splitlen(s_str) != 3 || !is_int(s_str[0])
		|| !is_int(s_str[1]) || !is_int(s_str[2]))
	{
		ft_freesplit(s_str);
		return (false);
	}
	color_ret->x = ft_atoi(s_str[0]);
	color_ret->y = ft_atoi(s_str[1]);
	color_ret->z = ft_atoi(s_str[2]);
	ft_freesplit(s_str);
	if (color_ret->x < 0 || color_ret->x > 255
		|| color_ret->y < 0 || color_ret->y > 255
		|| color_ret->z < 0 || color_ret->z > 255)
		return (false);
	return (true);
}
