/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:18:27 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 12:38:24 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	ft_on_echap_keypressed(t_mrt *mrt);

int	on_keypressed(int key, t_mrt *mrt)
{
	if (KDEBUG)
		ft_printf("Pressed key: %#x\n", key);
	if (key == KEY_ECHAP)
		ft_on_echap_keypressed(mrt);
	else if (key == KEY_X)
		mrt->event_mode.axis = X;
	else if (key == KEY_Y)
		mrt->event_mode.axis = Y;
	else if (key == KEY_Z)
		mrt->event_mode.axis = Z;
	else if (key == KEY_MODE_TRANSLATE)
		mrt->event_mode.mode = TRANSLATE;
	else if (key == KEY_MODE_RESIZE)
		mrt->event_mode.mode = RESIZE;
	else if (key == KEY_MODE_ROTATE)
		mrt->event_mode.mode = ROTATE;
	else if (key == KEY_FLAG_CAMERA)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_CAMERA);
	else if (key == KEY_FLAG_FOV)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_FOV_ZOOM);
	else if (key == KEY_FLAG_HEIGHT)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_HEIGHT);
	else if (key == KEY_FLAG_DIAMETER)
		ft_toggleflag(&mrt->event_mode.flags, FLAG_DIAMETER);
	return (0);
}

static void	ft_on_echap_keypressed(t_mrt *mrt)
{
	if (KDEBUG)
		ft_putstr("ECHAP key pressed \n");
	exit_mrt(*mrt, 0);
}

int	on_cross_clicked(t_mrt *mrt)
{
	if (KDEBUG)
		ft_putstr("Exit cross pressed \n");
	exit_mrt(*mrt, 0);
	return (0);
}
