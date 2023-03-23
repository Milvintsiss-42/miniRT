/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:45:00 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 17:31:50 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_color(char *str, int *color_ret)
{
	char	**s_str;
	int		r;
	int		g;
	int		b;

	s_str = ft_split(str, ',');
	if (!s_str)
		return (false);
	if (ft_splitlen(s_str) != 3 || !is_int(s_str[0])
		|| !is_int(s_str[1]) || !is_int(s_str[2]))
	{
		ft_freesplit(s_str);
		return (false);
	}
	r = ft_atoi(s_str[0]);
	g = ft_atoi(s_str[1]);
	b = ft_atoi(s_str[2]);
	*color_ret = (r << 16) + (g << 8) + b;
	ft_freesplit(s_str);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	return (true);
}
