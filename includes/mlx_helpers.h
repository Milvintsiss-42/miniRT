/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:47:46 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/21 07:20:45 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HELPERS_H
# define MLX_HELPERS_H

# include "common.h"

# define KEY_ECHAP		0xff1b
# define KEY_X			0x0078
# define KEY_Y			0x0079
# define KEY_Z			0x007a
# define KEY_ARROW_L	0xff51
# define KEY_ARROW_R	0xff53
# define KEY_ARROW_T	0xff52
# define KEY_ARROW_D	0xff54

# define MOUSE_LEFT			1
# define MOUSE_RIGHT		2
# define MOUSE_MIDDLE		3
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

void		put_pixel_on_img(t_mrt *mrt, int x, int y, int color);

int			reframe(t_mrt *mrt);
void		open_window(t_mrt *mrt, double width_fraction,
				double height_fraction);

int			on_keypressed(int keycode, t_mrt *mrt);
int			on_mousepressed(int button, int x, int y, t_mrt *mrt);
int			on_cross_clicked(t_mrt *mrt);

#endif
