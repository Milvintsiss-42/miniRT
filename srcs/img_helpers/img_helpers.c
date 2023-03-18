/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:31:13 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 21:43:06 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	destroy_img(t_mlx mlx, t_img img)
{
	if (img.img)
		mlx_destroy_image(mlx.mlx, img.img);
}

t_img	null_img(void)
{
	t_img	img;

	img.img = 0;
	img.addr = 0;
	img.bits_per_pixel = 0;
	img.endian = 0;
	img.line_len = 0;
	return (img);
}

t_img	create_empty_img(t_mrt mrt)
{
	t_img	img;

	img = null_img();
	img.img = mlx_new_image(mrt.mlx.mlx, mrt.mlx.win_width, mrt.mlx.win_height);
	if (!img.img)
		exit_mrt(mrt, ft_perror(mrt, ERR_MLXCRASH));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len,
			&img.endian);
	if (!img.addr)
		exit_mrt(mrt, ft_perror(mrt, ERR_MLXCRASH));
	return (img);
}
