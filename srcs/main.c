/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:58:25 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/19 18:38:50 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "mlx_helpers.h"

static void	init_mrt_data(t_mrt *mrt, int argc, char const **argv)
{
	if (argc < 1 || !argv[0])
		exit(1);
	mrt->bin_name = argv[0];
	mrt->mlx.mlx = 0;
	mrt->mlx.window = 0;
	mrt->mlx.win_height = 0;
	mrt->mlx.win_width = 0;
	mrt->img.current = null_img();
	mrt->img.future = null_img();
	mrt->scene.lights = 0;
	mrt->scene.objects = 0;
}

int	main(int argc, char const **argv)
{
	t_mrt	mrt;

	init_mrt_data(&mrt, argc, argv);
	open_window(&mrt, 0.5, 0.5);
	return (0);
}
