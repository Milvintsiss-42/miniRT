/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:58:16 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 15:03:53 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_specular(t_mrt *mrt, t_parsing *parsing, char *str,
	int *specular_ret)
{
	if (!parse_int(str, specular_ret))
		parsing_error(mrt, *parsing, ERR_INVALID_INT, true);
	if (*specular_ret < -1)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
}

void	parse_reflection(t_mrt *mrt, t_parsing *parsing, char *str,
	double *reflection_ret)
{
	if (!parse_double(str, reflection_ret))
		parsing_error(mrt, *parsing, ERR_INVALID_FLOATING_POINT, true);
	if (*reflection_ret < 0.0 || *reflection_ret > 1.0)
		parsing_error(mrt, *parsing, ERR_OUT_OF_RANGE, true);
}
