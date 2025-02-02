/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:25:57 by ple-stra          #+#    #+#             */
/*   Updated: 2025/01/28 01:45:00 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

int	reframe(t_mrt *mrt)
{
	if (mrt->img.fade_resolution < 1)
		return (0);
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
	create_new_img(mrt);
	draw_test_card_f(mrt);
	set_new_img_to_screen(mrt);
}

void	open_window(t_mrt *mrt, double width_fraction, double height_fraction)
{
	init_mlx_lib(mrt);
	setup_mlx_window(mrt, width_fraction, height_fraction);
	mlx_key_hook(mrt->mlx.window, on_keypressed, mrt);
	mlx_mouse_hook(mrt->mlx.window, on_mouse_event, mrt);
	mlx_hook(mrt->mlx.window, ON_DESTROY, 0, on_window_cross_clicked, mrt);
	mlx_loop_hook(mrt->mlx.mlx, reframe, mrt);
	mlx_loop(mrt->mlx.mlx);
}
