/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_helpers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:19:59 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/18 18:14:22 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_HELPERS_H
# define IMG_HELPERS_H

# include "common.h"

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mrt	t_mrt;
typedef struct s_mlx	t_mlx;

typedef struct s_img_garbage {
	t_img	current;
	t_img	future;
}	t_img_garbage;

void		create_new_img(t_mrt *mrt);
void		set_future_img(t_mrt *mrt, t_img img);
void		set_new_img_to_screen(t_mrt *mrt);

void		destroy_img(t_mlx mlx, t_img img);
t_img		null_img(void);
t_img		create_empty_img(t_mrt mrt);

#endif
