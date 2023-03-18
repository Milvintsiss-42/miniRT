/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:05:09 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 21:39:21 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include "mlx.h"
# include "img_helpers.h"

# define PROGRAM_NAME "miniRT"

# define ERR_UNKNOWN			"Unknown error"

# define ERR_WRG_NB_ARG			"Error: Incorrect number of arguments"
# define ERR_INV_EXT			"Error: Invalid file extension"
# define ERR_INV_FILE			"Error: Invalid file"

# define ERR_FAILED_INIT_MLX	"Error: Failed to init mlx"
# define ERR_FAILED_OP_WIN_MLX	"Error: Failed to open mlx window"
# define ERR_MLXCRASH			"Error: MLX crashed"

# define KEY_ECHAP		0xff1b

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	int		win_height;
	int		win_width;
}	t_mlx;

typedef struct s_mrt {
	const char		*bin_name;
	t_mlx			mlx;
	t_img_garbage	img;
}	t_mrt;

void		exit_mrt(t_mrt mrt, int status);

int			ft_perror(t_mrt mrt, const char *error_str);
int			ft_fperror(t_mrt mrt, const char *filename, const char *error_str);
int			ft_perror_errno(t_mrt mrt);
int			ft_fperror_errno(t_mrt mrt, const char *filename);

#endif
