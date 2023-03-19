/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:25:57 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 15:09:11 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "engine.h"

void	reframe(t_mrt *mrt)
{
	create_new_img(mrt);
	draw_frame(mrt);
	set_new_img_to_screen(mrt);
}

static void	init_mlx_lib(t_mrt *mrt)
{
	mrt->mlx.mlx = mlx_init();
	if (!mrt->mlx.mlx)
		exit_mrt(*mrt, ft_perror(*mrt, ERR_FAILED_INIT_MLX));
}

static void	setup_mlx_window(t_mrt *mrt, double width_fraction,
		double height_fraction)
{
	t_mlx	*mlx;

	mlx = &mrt->mlx;
	mlx_get_screen_size(mlx->mlx, &mlx->win_width, &mlx->win_height);
	mlx->win_width *= width_fraction;
	mlx->win_height *= height_fraction;
	mlx->window = mlx_new_window(mlx->mlx, mlx->win_width, mlx->win_height,
			PROGRAM_NAME);
	if (!mlx->window)
		exit_mrt(*mrt, ft_perror(*mrt, ERR_FAILED_OP_WIN_MLX));
}

void	open_window(t_mrt *mrt, double width_fraction, double height_fraction)
{
	init_mlx_lib(mrt);
	setup_mlx_window(mrt, width_fraction, height_fraction);
	reframe(mrt);
	mlx_loop(mrt->mlx.mlx);
}
