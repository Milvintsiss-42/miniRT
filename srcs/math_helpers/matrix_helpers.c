/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:55:06 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/19 00:55:30 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

/// @brief Rotates a vector using roll (Φ(Phi) or α(alpha)), yaw (Ψ(Psi) or
/// γ(Gamma)) and pitch (θ(Theta) or β(Beta)).
/// 2π being a full rotation around an axis.
/// @param vec The vector to rotate.
/// @param roll A positive value will be equivalent to you twisting your head
/// to the right and acting really weird.
/// @param yaw A positive value will be equivalent to moving your head to look
/// at your right.
/// @param pitch A positive value will be equivalent to moving your head to look
/// up.
/// @return The rotated vector.
t_vec3	rotate_vec3(t_vec3 vec, double roll, double yaw, double pitch)
{
	t_vec3	ret;

	roll = -roll;
	yaw = -yaw;
	pitch = -pitch;
	ret.x = vec.x * cos(roll) * cos(yaw)
		+ vec.y * (-sin(roll) * cos(pitch) - cos(roll) * sin(yaw)
			* sin(pitch))
		+ vec.z * (sin(roll) * sin(pitch) - cos(roll) * sin(yaw)
			* cos(pitch));
	ret.y = vec.x * sin(roll) * cos(yaw)
		+ vec.y * (cos(roll) * cos(pitch) - sin(roll) * sin(yaw)
			* sin(pitch))
		+ vec.z * (-cos(roll) * sin(pitch) - sin(roll) * sin(yaw)
			* cos(pitch));
	ret.z = vec.x * sin(yaw)
		+ vec.y * cos(yaw) * sin(pitch)
		+ vec.z * cos(yaw) * cos(pitch);
	return (ret);
}
