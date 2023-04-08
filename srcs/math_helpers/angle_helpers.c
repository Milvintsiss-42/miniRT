/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:41:21 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/08 17:45:57 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}
