/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:58:25 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/20 15:32:13 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "parsing.h"
#include "mlx_helpers.h"

static void	verify_args(t_mrt mrt, int argc, char const **argv)
{
	if (argc != 2)
		exit_mrt(mrt, ft_perror(mrt, "Usage: ./miniRT scene_file.rt"));
	if (ft_strlen(argv[1]) < 3
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 4) != 0)
		exit_mrt(mrt, ft_perror(mrt, ERR_INVALID_FILE_EXTENSION));
}

static void	init_scene_values(t_scene *scene)
{
	scene->amb_light.brightness = -1;
	scene->amb_light.color = -1;
	scene->camera.fov = -1;
	scene->camera.origin = (t_vec3){-1, -1, -1};
	scene->camera.orientation = (t_vec3){-1, -1, -1};
	scene->lights = 0;
	scene->objects = 0;
}

static void	init_mrt_data(t_mrt *mrt, int argc, char const **argv)
{
	if (argc < 1 || !argv[0])
		exit(1);
	mrt->bin_name = ft_basename(argv[0]);
	mrt->mlx.mlx = 0;
	mrt->mlx.window = 0;
	mrt->mlx.win_height = 0;
	mrt->mlx.win_width = 0;
	mrt->img.current = null_img();
	mrt->img.future = null_img();
	init_scene_values(&mrt->scene);
}

int	main(int argc, char const **argv)
{
	t_mrt	mrt;

	init_mrt_data(&mrt, argc, argv);
	verify_args(mrt, argc, argv);
	parse_scene(&mrt, argv[1]);
	open_window(&mrt, 0.5, 0.5);
	return (0);
}
