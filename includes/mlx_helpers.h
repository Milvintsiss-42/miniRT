/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:47:46 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 13:40:43 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HELPERS_H
# define MLX_HELPERS_H

# define KEY_ECHAP		0xff1b
# define KEY_X			0x0078
# define KEY_Y			0x0079
# define KEY_Z			0x007a
# define KEY_ARROW_L	0xff51
# define KEY_ARROW_R	0xff53
# define KEY_ARROW_T	0xff52
# define KEY_ARROW_D	0xff54
# define KEY_S			0x0073
# define KEY_R			0x0072
# define KEY_T			0x0074
# define KEY_C			0x0063
# define KEY_D			0x0064
# define KEY_F			0x0066
# define KEY_H			0x0068

# define KEY_MODE_RESIZE	KEY_S
# define KEY_MODE_ROTATE	KEY_R
# define KEY_MODE_TRANSLATE	KEY_T

# define KEY_FLAG_HEIGHT	KEY_H
# define KEY_FLAG_DIAMETER	KEY_D
# define KEY_FLAG_CAMERA	KEY_C
# define KEY_FLAG_FOV		KEY_F

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

# define TRANSLATE_SPEED		0.1
# define RESIZE_SPEED			0.1
# define ROTATE_SPEED			0.01
# define LIGHT_INTENSITY_SPEED	0.01

typedef enum e_mode
{
	RESIZE,
	ROTATE,
	TRANSLATE,
}	t_mode;

typedef enum e_axis
{
	X,
	Y,
	Z,
}	t_axis;

# define FLAG_DIAMETER	0b00000001
# define FLAG_HEIGHT	0b00000010
# define FLAG_CAMERA	0b00000100
# define FLAG_FOV_ZOOM	0b00001000

typedef struct s_event_mode
{
	t_mode	mode;
	t_axis	axis;
	int		flags;
}	t_event_mode;

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	int		win_height;
	int		win_width;
}	t_mlx;

typedef struct s_mrt		t_mrt;

void		put_pixel_on_img(t_mrt *mrt, int x, int y, int color);

int			reframe(t_mrt *mrt);
void		open_window(t_mrt *mrt, double width_fraction,
				double height_fraction);

int			on_keypressed(int keycode, t_mrt *mrt);
int			on_mouse_event(int button, int x, int y, t_mrt *mrt);
int			on_cross_clicked(t_mrt *mrt);

#endif
