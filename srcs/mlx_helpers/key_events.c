/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:18:27 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/27 16:31:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static bool	key_echap(t_mrt *mrt, int key)
{
	if (key != KEY_ECHAP)
		return (false);
	if (KDEBUG)
		ft_putstr("ECHAP key pressed \n");
	exit_mrt(*mrt, 0);
	return (true);
}

static bool	key_mode(t_mrt *mrt, int key)
{
	if (key == KEY_MODE_TRANSLATE)
		mrt->event_mode.mode = TRANSLATE;
	else if (key == KEY_MODE_RESIZE)
		mrt->event_mode.mode = RESIZE;
	else if (key == KEY_MODE_ROTATE)
		mrt->event_mode.mode = ROTATE;
	else
		return (false);
	return (true);
}

static bool	key_axis(t_mrt *mrt, int key)
{
	if (key == KEY_X)
		mrt->event_mode.axis = X;
	else if (key == KEY_Y)
		mrt->event_mode.axis = Y;
	else if (key == KEY_Z)
		mrt->event_mode.axis = Z;
	else
		return (false);
	return (true);
}

static bool	key_flag(t_mrt *mrt, int key)
{
	if (key == KEY_FLAG_CAMERA)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_CAMERA);
	else if (key == KEY_FLAG_FOV)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_FOV_ZOOM);
	else if (key == KEY_FLAG_HEIGHT)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_HEIGHT);
	else if (key == KEY_FLAG_DIAMETER)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_DIAMETER);
	else if (key == KEY_FLAG_LIGHT_V)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_LIGHT_V);
	else if (key == KEY_FLAG_AMB_LIGHT)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_AMB_LIGHT);
	else if (key == KEY_FLAG_REFLECT)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_REFLECT);
	else
		return (false);
	return (true);
}

int	on_keypressed(int key, t_mrt *mrt)
{
	if (KDEBUG)
		ft_printf("Pressed key: %#x\n", key);
	if (key_echap(mrt, key)
		|| key_mode(mrt, key)
		|| key_axis(mrt, key)
		|| key_flag(mrt, key))
		return (true);
	else if (key == KEY_UNSELECT_ALL)
		unselect_all_objects(mrt);
	else
		return (false);
	return (true);
}
