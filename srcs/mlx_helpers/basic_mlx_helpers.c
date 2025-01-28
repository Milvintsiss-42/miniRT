/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_mlx_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:52:26 by ple-stra          #+#    #+#             */
/*   Updated: 2025/01/28 03:44:52 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	put_pixel_on_img(t_mrt *mrt, int x, int y, int color)
{
	t_img	img;
	char	*dest;

	img = mrt->img.future;
	if (x >= 0 && x < mrt->mlx.win_width && y >= 0 && y < mrt->mlx.win_height)
	{
		dest = img.addr + (y * img.line_len + x * (img.bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

int	get_color_of_pixel_on_img(t_mrt *mrt, t_img img, int x, int y)
{
	char	*src;

	if (x >= 0 && x < mrt->mlx.win_width && y >= 0 && y < mrt->mlx.win_height)
	{
		src = img.addr + (y * img.line_len + x * (img.bits_per_pixel / 8));
		return (*(unsigned int *)src);
	}
	return (-1);
}
