/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:35:34 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/21 10:31:40 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

t_l_obj	*select_object(t_mrt *mrt, int x, int y)
{
	t_vec3		ray_dir;
	t_intersect	intersect;

	ray_dir = get_ray_direction(mrt, x, y);
	intersect = closest_intersection(mrt, mrt->scene.camera.origin, ray_dir,
			1.0, __DBL_MAX__);
	if (!intersect.obj)
		return (NULL);
	intersect.obj->is_selected = !intersect.obj->is_selected;
	return (intersect.obj);
}

void	on_mousescroll(t_mrt *mrt, int direction)
{
	mrt->scene.camera.fov -= direction;
	mrt->scene.camera.fov = ft_max(1, ft_min(mrt->scene.camera.fov, 179));
}

int	on_mousepressed(int button, int x, int y, t_mrt *mrt)
{
	if (KDEBUG)
		ft_printf("Mouse click: %d at %d, %d\n", button, x, y);
	if (button == MOUSE_LEFT)
		select_object(mrt, x, y);
	else if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		on_mousescroll(mrt, 1 - 2 * (button == MOUSE_SCROLL_DOWN));
	return (0);
}
