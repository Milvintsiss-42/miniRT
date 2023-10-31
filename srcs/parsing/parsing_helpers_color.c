/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:45:00 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/31 16:00:11 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	are_commas_placed_correctly(char *str)
{
	if (!*str || *str == ',')
		return (false);
	while (*(str + 1))
	{
		if (*str == ',' && *(str + 1) == ',')
			return (false);
		str++;
	}
	if (*str == ',')
		return (false);
	return (true);
}

// We use t_vec3 to store colors, so x corresponds to red, y to green
// and z to blue.
bool	parse_color(char *str, t_vec3 *color_ret)
{
	char	**s_str;

	if (!are_commas_placed_correctly(str))
		return (false);
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
