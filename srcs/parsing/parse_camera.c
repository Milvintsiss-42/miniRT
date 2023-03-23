/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:23:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/03/23 17:37:27 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_camera(t_mrt *mrt, t_parsing *parsing)
{
	t_camera	*camera;

	camera = &mrt->scene.camera;
	if (camera->fov != -1)
		parsing_error(mrt, *parsing, ERR_MULTIPLE_CAMERA, true);
	if (ft_splitlen(parsing->s_line) != 4)
		parsing_error(mrt, *parsing, ERR_INVALID_NUMBER_OF_ARGUMENTS, true);
	if (!parse_vector(parsing->s_line[1], &camera->origin))
		parsing_error(mrt, *parsing, ERR_INVALID_VECTOR, true);
	if (!parse_normalized_vector(parsing->s_line[2], &camera->orientation))
		parsing_error(mrt, *parsing, ERR_INVALID_NORM_VECTOR, true);
	if (!parse_int(parsing->s_line[3], &camera->fov))
		parsing_error(mrt, *parsing, ERR_INVALID_INT, true);
	if (camera->fov < 0 || camera->fov > 180)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
}
