/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test_card_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:24:43 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/12 17:53:04 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helpers.h"

// See https://youtu.be/Qz0KTGYJtUk?t=544 for detailled explanations
static unsigned long long	random_number(unsigned long long *state)
{
	unsigned long long	r;
	unsigned long long	seed;

	seed = (unsigned long long)*state;
	seed = seed * 7454651516 + 468443135;
	r = ((seed >> ((seed >> 28) + 4)) ^ seed) * 2685821657736338717;
	r = (r >> 22) ^ r;
	r = r / 9007199254740992.0;
	*state = r;
	return (r);
}

static int	random_color_from_seed(unsigned long long state)
{
	int		r;
	int		g;
	int		b;

	r = (int)(random_number(&state)) % 255;
	g = (int)(random_number(&state)) % 255;
	b = (int)(random_number(&state)) % 255;
	return (r << 16 | g << 8 | b);
}

void	draw_test_card_f(t_mrt *mrt)
{
	int					x;
	int					y;
	unsigned long long	seed;

	x = 0;
	while (x < mrt->mlx.win_width)
	{
		y = 0;
		while (y < mrt->mlx.win_height)
		{
			seed = y * mrt->mlx.win_width + x;
			put_pixel_on_img(mrt, x, y, random_color_from_seed(seed));
			y++;
		}
		x++;
		print_progress(x, mrt->mlx.win_width);
	}
}
