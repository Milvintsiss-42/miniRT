/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:25:57 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/21 03:11:45 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

int	reframe(t_mrt *mrt)
{
	create_new_img(mrt);
	draw_frame(mrt);
	set_new_img_to_screen(mrt);
	return (0);
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
	if (KDEBUG)
		ft_printf("Screen size: %d x %d\n", mlx->win_width, mlx->win_height);
	mlx->win_width *= width_fraction;
	mlx->win_height *= height_fraction;
	if (KDEBUG)
		ft_printf("Window size: %d x %d\n", mlx->win_width, mlx->win_height);
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
	mlx_key_hook(mrt->mlx.window, on_keypressed, mrt);
	mlx_hook(mrt->mlx.window, 17, 0, on_cross_clicked, mrt);
	mlx_loop_hook(mrt->mlx.mlx, reframe, mrt);
	mlx_loop(mrt->mlx.mlx);
}
