/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:16:37 by ple-stra          #+#    #+#             */
/*   Updated: 2023/08/17 03:55:27 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns biggest int between [a] and [b].
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// Returns smallest int between [a] and [b].
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// Returns biggest double between [a] and [b].
double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// Returns smallest double between [a] and [b].
double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
