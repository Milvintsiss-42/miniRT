/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:47:46 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 15:10:10 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HELPERS_H
# define MLX_HELPERS_H

# include "common.h"

void		put_pixel_on_img(t_mrt *mrt, int x, int y, int color);

void		reframe(t_mrt *mrt);
void		open_window(t_mrt *mrt, double width_fraction,
				double height_fraction);

#endif
