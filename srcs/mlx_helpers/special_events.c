/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 02:10:55 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/23 02:12:23 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	on_window_cross_clicked(t_mrt *mrt)
{
	if (KDEBUG)
		ft_putstr("Exit cross pressed \n");
	exit_mrt(*mrt, 0);
	return (0);
}
