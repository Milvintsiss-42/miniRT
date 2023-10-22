/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:05:09 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/22 11:21:31 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdbool.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_helpers.h"
# include "engine.h"
# include "img_helpers.h"

# define PROGRAM_NAME "miniRT"

# ifndef KDEBUG
#  define KDEBUG 0
# endif

# define ERR_UNKNOWN			"Unknown error"

# define ERR_WRG_NB_ARG			"Incorrect number of arguments"

# define ERR_FAILED_INIT_MLX	"MiniLibX: Failed to init mlx"
# define ERR_FAILED_OP_WIN_MLX	"MiniLibX: Failed to open mlx window"
# define ERR_MLXCRASH			"MiniLibX: MLX crashed"

# define KEY_ECHAP		0xff1b

# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF
# define WHITE				0xFFFFFF
# define BLACK				0x000000
# define NATURAL_LIGHT 		0xF1EBC8

# define BACKGROUND_COLOR	NATURAL_LIGHT

typedef struct s_mrt {
	const char		*bin_name;
	t_mlx			mlx;
	t_img_garbage	img;
	t_scene			scene;
	t_event_mode	event_mode;
}	t_mrt;

void		exit_mrt(t_mrt mrt, int status);

int			ft_perror(t_mrt mrt, const char *error_str);
int			ft_ctxtperror(t_mrt mrt, const char *filename,
				const char *error_str);
int			ft_perror_errno(t_mrt mrt);
int			ft_ctxtperror_errno(t_mrt mrt, const char *filename);

const char	*ft_basename(const char *path);

void		print_progress(int progress, int start, int total);

#endif
