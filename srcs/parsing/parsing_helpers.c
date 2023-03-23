/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:13:23 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 17:41:03 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	is_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		else if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_double(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		else if (str[i] == '\n')
			break ;
		else if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (dot > 1)
		return (false);
	return (true);
}

bool	parse_int(char *str, int *int_ret)
{
	if (!is_int(str))
		return (false);
	*int_ret = ft_atoi(str);
	return (true);
}

bool	parse_double(char *str, double *double_ret)
{
	if (!is_double(str))
		return (false);
	*double_ret = ft_atof(str);
	return (true);
}
