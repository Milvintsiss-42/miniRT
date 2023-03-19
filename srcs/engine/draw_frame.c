/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:59:41 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 15:06:59 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helpers.h"
#include <time.h>
#include <stdlib.h>

void	draw_frame(t_mrt *mrt)
{
	int	x;
	int	y;

	x = 0;
	srand(time(NULL));
	while (x < mrt->mlx.win_width)
	{
		y = 0;
		while (y < mrt->mlx.win_height)
		{
			put_pixel_on_img(mrt, x, y, rand());
			y++;
		}
		x++;
	}
}
