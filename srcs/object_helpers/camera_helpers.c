/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 09:35:14 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 13:24:00 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// See method rotate_vec3 in srcs/math_helpers/matrix_helpers.c for more info.
void	rotate_camera(t_mrt *mrt, double yaw, double pitch, double roll)
{
	mrt->scene.camera.yaw += yaw;
	mrt->scene.camera.pitch += pitch;
	mrt->scene.camera.roll += roll;
}

void	translate_camera(t_mrt *mrt, t_axis axis, int direction)
{
	mrt->scene.camera.origin = (t_vec3){
		mrt->scene.camera.origin.x + (direction * TRANSLATE_SPEED
			* (axis == X)),
		mrt->scene.camera.origin.y + (direction * TRANSLATE_SPEED
			* (axis == Y)),
		mrt->scene.camera.origin.z + (direction * TRANSLATE_SPEED
			* (axis == Z))};
}

void	camera_natural_zoom(t_mrt *mrt, int direction, int x, int y)
{
	t_vec3	camera_orientation;

	camera_orientation = rotate_vec3(canvas_to_viewport(mrt, x, y),
			mrt->scene.camera.roll,
			mrt->scene.camera.yaw,
			mrt->scene.camera.pitch);
	camera_orientation = vec3_normalize(camera_orientation);
	mrt->scene.camera.origin = vec3_sum(
			mrt->scene.camera.origin,
			vec3_scal_prdct(camera_orientation, direction));
}

void	camera_fov_zoom(t_mrt *mrt, int direction)
{
	mrt->scene.camera.fov -= direction;
	mrt->scene.camera.fov = ft_max(1, ft_min(mrt->scene.camera.fov, 179));
}
