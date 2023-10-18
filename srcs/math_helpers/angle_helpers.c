/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:41:21 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/19 01:25:50 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"
#include "libft.h"

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

// Compute the angle between [vec1] and [vec2].
double	vec3_ang_btwn(t_vec3 vec1, t_vec3 vec2)
{
	double	magnitude1;
	double	magnitude2;
	double	dot_prdct;

	magnitude1 = vec3_magnitude(vec1);
	magnitude2 = vec3_magnitude(vec2);
	dot_prdct = vec3_dot_prdct(vec1, vec2);
	return (acos(ft_min_d(dot_prdct / (magnitude1 * magnitude2), 1.0)));
}
