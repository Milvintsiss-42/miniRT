/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:35:13 by ple-stra          #+#    #+#             */
/*   Updated: 2023/06/15 14:06:23 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "parsing.h"
#include <fcntl.h>

void	parsing_error(t_mrt *mrt, t_parsing parsing, char *error,
	bool show_line)
{
	if (parsing.line)
		free(parsing.line);
	if (parsing.s_line)
		ft_freesplit(parsing.s_line);
	if (parsing.fd)
		close(parsing.fd);
	if (parsing.line && parsing.fd)
		clean_gnl_for_fd(parsing.fd);
	if (show_line)
		ft_printf_fd(2, "Error\n%s at line %d\n", error, parsing.nline);
	else
		ft_printf_fd(2, "Error\n%s\n", error);
	exit_mrt(*mrt, 1);
}

static bool	get_info_from_line(t_mrt *mrt, t_parsing *parsing)
{
	if (ft_strcmp(parsing->s_line[0], "A") == 0)
		set_ambiant_light(mrt, parsing);
	else if (ft_strcmp(parsing->s_line[0], "C") == 0)
		set_camera(mrt, parsing);
	else if (ft_strcmp(parsing->s_line[0], "sl") == 0)
		add_light(mrt, parsing, false);
	else if (ft_strcmp(parsing->s_line[0], "dl") == 0)
		add_light(mrt, parsing, true);
	else if (ft_strcmp(parsing->s_line[0], "sp") == 0)
		add_sphere(mrt, parsing);
	else if (ft_strcmp(parsing->s_line[0], "pl") == 0)
		add_plane(mrt, parsing);
	else if (ft_strcmp(parsing->s_line[0], "cy") == 0)
		add_cylinder(mrt, parsing);
	else if (ft_strcmp(parsing->s_line[0], "#") != 0)
		return (false);
	return (true);
}

static void	parse_line(t_mrt *mrt, t_parsing *parsing)
{
	if (ft_strcmp(parsing->line, "\n") == 0)
		return ;
	parsing->s_line = ft_split(parsing->line, ' ');
	if (!parsing->s_line)
		parsing_error(mrt, *parsing, ERR_UNEXPECTED_ERROR, false);
	if (!get_info_from_line(mrt, parsing))
		parsing_error(mrt, *parsing, ERR_UNKNOWN_ELEMENT, true);
	ft_freesplit(parsing->s_line);
	parsing->s_line = 0;
}

void	parse_scene(t_mrt *mrt, const char *file_path)
{
	t_parsing	parsing;

	parsing.nline = 0;
	parsing.line = 0;
	parsing.s_line = 0;
	parsing.fd = open(file_path, O_RDONLY);
	if (parsing.fd < 0)
		parsing_error(mrt, parsing, ERR_CANNOT_OPEN_FILE, false);
	parsing.line = get_next_line(parsing.fd);
	if (!parsing.line)
		parsing_error(mrt, parsing, ERR_EMPTY_OR_INVALID, false);
	while (parsing.line)
	{
		parsing.nline++;
		parse_line(mrt, &parsing);
		free(parsing.line);
		parsing.line = get_next_line(parsing.fd);
	}
	if (mrt->scene.camera.fov == -1 || mrt->scene.amb_light.brightness == -1)
		parsing_error(mrt, parsing, ERR_NEED_AMBIANT_AND_CAMERA, false);
	close(parsing.fd);
}
