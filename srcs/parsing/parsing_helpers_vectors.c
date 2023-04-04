/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers_vectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:29:21 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/04 21:58:41 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_vector(char *str, t_vec3 *vector_ret)
{
	char	**s_str;

	s_str = ft_split(str, ',');
	if (!s_str)
		return (false);
	if (ft_splitlen(s_str) != 3 || !is_double(s_str[0])
		|| !is_double(s_str[1]) || !is_double(s_str[2]))
	{
		ft_freesplit(s_str);
		return (false);
	}
	vector_ret->x = ft_atof(s_str[0]);
	vector_ret->y = ft_atof(s_str[1]);
	vector_ret->z = ft_atof(s_str[2]);
	ft_freesplit(s_str);
	return (true);
}

bool	parse_normalized_vector(char *str, t_vec3 *vector_ret)
{
	if (!parse_vector(str, vector_ret))
		return (false);
	if (vector_ret->x < -1 || vector_ret->x > 1
		|| vector_ret->y < -1 || vector_ret->y > 1
		|| vector_ret->z < -1 || vector_ret->z > 1)
		return (false);
	return (true);
}
