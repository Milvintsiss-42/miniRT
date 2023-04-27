/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_products.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:53:12 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/27 22:55:36 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

// Compute the scalar product between a vector and a value.
t_vec3	vec3_scal_prdct(t_vec3 vec, double scalar)
{
	t_vec3	ret;

	ret.x = vec.x * scalar;
	ret.y = vec.y * scalar;
	ret.z = vec.z * scalar;
	return (ret);
}

// Compute the dot product of [vec1] and [vec2].
double	vec3_dot_prdct(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

// Compute the cross product of [vec1] and [vec2] as r = vec1 x vec2.
t_vec3	vec3_cross_prdct(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (ret);
}
