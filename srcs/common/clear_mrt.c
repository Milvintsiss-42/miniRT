/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:54:13 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 21:30:49 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	free_mlx(t_mlx mlx)
{
	if (!mlx.mlx)
		return ;
	if (mlx.window)
		mlx_destroy_window(mlx.mlx, mlx.window);
	mlx_destroy_display(mlx.mlx);
	free(mlx.mlx);
}

static void	free_mrt(t_mrt mrt)
{
	destroy_img(mrt.mlx, mrt.img.current);
	destroy_img(mrt.mlx, mrt.img.future);
	free_mlx(mrt.mlx);
}

void	exit_mrt(t_mrt mrt, int status)
{
	free_mrt(mrt);
	exit(status);
}
