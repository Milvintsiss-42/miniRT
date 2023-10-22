/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:35:34 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 13:28:29 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

static void	apply_modifiers_to_objs(t_mrt *mrt, int direction)
{
	if (mrt->event_mode.mode == TRANSLATE)
		apply_modifier_to_selected_objs(mrt, translate_object, direction);
	else if (mrt->event_mode.mode == RESIZE)
		apply_modifier_to_selected_objs(mrt, resize_object, direction);
	else if (mrt->event_mode.mode == ROTATE)
		apply_modifier_to_selected_objs(mrt, rotate_object, direction);
}

static void	apply_modifiers_to_camera(t_mrt *mrt, int direction, int x, int y)
{
	if (mrt->event_mode.mode == RESIZE)
	{
		if (ft_checkflag(mrt->event_mode.flags, FLAG_FOV_ZOOM))
			camera_fov_zoom(mrt, direction);
		else
			camera_natural_zoom(mrt, direction, x, y);
	}
	else if (mrt->event_mode.mode == ROTATE)
		rotate_camera(mrt,
			direction * ROTATE_SPEED * (mrt->event_mode.axis == X),
			direction * ROTATE_SPEED * (mrt->event_mode.axis == Y),
			direction * ROTATE_SPEED * (mrt->event_mode.axis == Z));
	else if (mrt->event_mode.mode == TRANSLATE)
		translate_camera(mrt, mrt->event_mode.axis, direction);
}

static void	on_mouse_scroll(t_mrt *mrt, int direction, int x, int y)
{
	if (ft_checkflag(mrt->event_mode.flags, FLAG_CAMERA))
		apply_modifiers_to_camera(mrt, direction, x, y);
	else
		apply_modifiers_to_objs(mrt, direction);
}

int	on_mouse_event(int button, int x, int y, t_mrt *mrt)
{
	if (KDEBUG)
		ft_printf("Mouse click: %d at %d, %d\n", button, x, y);
	if (button == MOUSE_LEFT)
		select_object_at_screen_coord(mrt, x, y);
	else if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		on_mouse_scroll(mrt, 1 - 2 * (button == MOUSE_SCROLL_DOWN), x, y);
	return (0);
}
