/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_products.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:53:12 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 20:40:00 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

/// @brief Computes the scalar product between a vector and a value as
/// `r = vec * value`.
/// Basicaly a scalar product is multiplying each component of a vector by a
/// value, the result is a vector with the same direction as the original vector
/// but with a different magnitude ([value] > 1: longer, [value] < 1: shorter).
/// @param vec
/// @param value
/// @return
t_vec3	vec3_scal_prdct(t_vec3 vec, double value)
{
	t_vec3	ret;

	ret.x = vec.x * value;
	ret.y = vec.y * value;
	ret.z = vec.z * value;
	return (ret);
}

/// @brief Computes the dot product (or inner product) of [vec1] and [vec2] as
/// `r = vec1 · vec2` or r = ⟨vec1, vec2⟩.
/// The dot product is the sum of the products between each component of
/// [vec1] and [vec2]. So:
/// ```
/// r = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z + vec2.z.
/// ```
/// @param vec1
/// @param vec2
/// @return
double	vec3_dot_prdct(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

/// @brief Computes the cross product of [vec1] and [vec2] as `r = vec1 X vec2`.
/// The cross product of the 2 vectors is a vector perpendicular to both [vec1]
/// and [vec2].
/// @param vec1
/// @param vec2
/// @return
t_vec3	vec3_cross_prdct(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (ret);
}
