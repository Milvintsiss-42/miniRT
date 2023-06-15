/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:29:32 by ple-stra          #+#    #+#             */
/*   Updated: 2023/06/15 16:24:46 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "common.h"

# define ERR_INVALID_FILE_EXTENSION "Invalid file extension"
# define ERR_CANNOT_OPEN_FILE "Cannot open file"
# define ERR_EMPTY_OR_INVALID "Empty or invalid file"
# define ERR_NEED_AMBIANT_AND_CAMERA "Need at least one ambiant light and one\
 camera"
# define ERR_MULTIPLE_AMBIANT "You cannot have multiple ambiant lights"
# define ERR_MULTIPLE_CAMERA "You cannot have multiple cameras"
# define ERR_UNEXPECTED_ERROR "Unexpected error"
# define ERR_UNKNOWN_ELEMENT "Unknown element"
# define ERR_INVALID_NUMBER_OF_ARGUMENTS "Invalid number of arguments"
# define ERR_INVALID_COLOR "Invalid color"
# define ERR_INVALID_VECTOR "Invalid vector"
# define ERR_INVALID_NORM_VECTOR "Invalid normalized vector"
# define ERR_INVALID_FLOATING_POINT "Invalid floating point number"
# define ERR_INVALID_INT "Invalid int number"
# define ERR_OUT_OF_RANGE "Out of range value"

typedef struct s_parsing
{
	int		fd;
	char	*line;
	char	**s_line;
	int		nline;
}	t_parsing;

void		parsing_error(t_mrt *mrt, t_parsing parsing, char *error,
				bool show_line);
void		parse_scene(t_mrt *mrt, const char *file_path);

void		set_ambiant_light(t_mrt *mrt, t_parsing *parsing);
void		set_camera(t_mrt *mrt, t_parsing *parsing);
void		add_light(t_mrt *mrt, t_parsing *parsing, bool is_directional);
void		add_sphere(t_mrt *mrt, t_parsing *parsing);
void		add_plane(t_mrt *mrt, t_parsing *parsing);
void		add_cylinder(t_mrt *mrt, t_parsing *parsing);

bool		parse_color(char *str, t_vec3 *color_ret);
bool		is_int(char *str);
bool		parse_int(char *str, int *int_ret);
bool		is_double(char *str);
bool		parse_double(char *str, double *double_ret);
bool		parse_vector(char *str, t_vec3 *vector_ret);
bool		parse_normalized_vector(char *str, t_vec3 *vector_ret);

#endif
