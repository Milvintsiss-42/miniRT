/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_garbage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:06:15 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 21:30:51 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	create_new_img(t_mrt *mrt)
{
	set_future_img(mrt, create_empty_img(*mrt));
}

void	set_future_img(t_mrt *mrt, t_img img)
{
	if (mrt->img.future.img != 0)
		destroy_img(mrt->mlx, mrt->img.future);
	mrt->img.future = img;
}

void	set_new_img_to_screen(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.window, mrt->img.future.img,
		0, 0);
	destroy_img(mrt->mlx, mrt->img.current);
	mrt->img.current = mrt->img.future;
	mrt->img.future = null_img();
}
