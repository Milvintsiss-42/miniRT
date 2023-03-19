/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:18:27 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 15:34:09 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helpers.h"

static void	ft_on_echap_keypressed(t_mrt *mrt);

int	on_keypressed(int key, t_mrt *mrt)
{
	if (key == KEY_ECHAP)
		ft_on_echap_keypressed(mrt);
	if (KDEBUG)
		ft_printf("Pressed key: %#x\n", key);
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
