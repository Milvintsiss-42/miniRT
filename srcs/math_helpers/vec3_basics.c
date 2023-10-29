/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:23:46 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/27 17:58:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

// Compute the square of the magnitude of a vector.
double	vec3_pow2(t_vec3 vec)
{
	return (vec3_dot_prdct(vec, vec));
}

// Compute the magnitude of a vector.
double	vec3_magnitude(t_vec3 vec)
{
	return (sqrt(vec3_pow2(vec)));
}

// Compute the sum of [vec1] and [vec2].
t_vec3	vec3_sum(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

// Compute the difference between [vec1] and [vec2] as r = vec1 - vec2.
t_vec3	vec3_diff(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;

	ret.x = vec1.x - vec2.x;
	ret.y = vec1.y - vec2.y;
	ret.z = vec1.z - vec2.z;
	return (ret);
}

// Compute a normalized vector of [vec].
t_vec3	vec3_normalize(t_vec3 vec)
{
	t_vec3	ret;
	double	magnitude;

	magnitude = vec3_magnitude(vec);
	ret.x = vec.x / magnitude;
	ret.y = vec.y / magnitude;
	ret.z = vec.z / magnitude;
	return (ret);
}
