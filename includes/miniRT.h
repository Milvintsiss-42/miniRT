/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:05:09 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/15 19:23:53 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define PROGRAM_NAME "miniRT"

# define ERR_WRG_NB_ARG			"Error: Incorrect number of arguments"
# define ERR_INV_EXT			"Error: Invalid file extension"
# define ERR_INV_FILE			"Error: Invalid file"

# define ERR_FAILED_INIT_MLX	"Error: Failed to init mlx"
# define ERR_FAILED_OP_WIN_MLX	"Error: Failed to open mlx window"
# define ERR_MLXCRASH			"Error: MLX crashed"

# define KEY_ECHAP		0xff1b

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_img_garbage {
	t_img	current;
	t_img	future;
}	t_img_garbage;

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	int		win_height;
	int		win_width;
}	t_mlx;

typedef struct s_mrt {
	t_mlx			mlx;
	t_img_garbage	img;
}	t_fdf;

#endif
