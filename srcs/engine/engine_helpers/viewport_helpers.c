/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 00:50:28 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 00:54:11 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	set_viewport_dimensions(t_mrt *mrt)
{
	mrt->scene.viewport.w = 1.0;
	mrt->scene.viewport.h = 1.0;
	if (mrt->mlx.win_width >= mrt->mlx.win_height)
	{
		mrt->scene.viewport.w
			= mrt->scene.viewport.w * mrt->mlx.win_width / mrt->mlx.win_height;
		mrt->scene.viewport.dist = (mrt->scene.viewport.w / 2.0)
			/ tan(deg_to_rad(mrt->scene.camera.fov / 2.0));
	}
	else
	{
		mrt->scene.viewport.h
			= mrt->scene.viewport.h * mrt->mlx.win_height / mrt->mlx.win_width;
		mrt->scene.viewport.dist = (mrt->scene.viewport.h / 2.0)
			/ tan(deg_to_rad(mrt->scene.camera.fov / 2.0));
	}
}

/// @brief Converts a pixel coordinate on the canvas to a viewport coordinate.
/// @param mrt
/// @param x
/// @param y
/// @return Returns a t_vec3 containing the viewport coordinates.
t_vec3	canvas_to_viewport(t_mrt *mrt, int x, int y)
{
	t_vec3	vp;

	x -= mrt->mlx.win_width / 2;
	y = mrt->mlx.win_height / 2 - y;
	vp.x = x * mrt->scene.viewport.w / mrt->mlx.win_width;
	vp.y = y * mrt->scene.viewport.h / mrt->mlx.win_height;
	vp.z = mrt->scene.viewport.dist;
	return (vp);
}
