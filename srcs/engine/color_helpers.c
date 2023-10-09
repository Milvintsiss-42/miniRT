/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:56 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/09 08:40:16 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

int	t_vec3_color_to_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.x;
	g = (int)color.y;
	b = (int)color.z;
	return (r << 16 | g << 8 | b);
}

t_vec3	int_color_to_t_vec3(int color)
{
	t_vec3	vec;

	vec.x = (color & 0xFF0000) >> 16;
	vec.y = (color & 0xFF00) >> 8;
	vec.z = (color & 0xFF);
	return (vec);
}

int	blend_colors(int color1, int color2, double ratio)
{
	t_vec3	c1;
	t_vec3	c2;
	t_vec3	r;

	c1 = int_color_to_t_vec3(color1);
	c2 = int_color_to_t_vec3(color2);
	r.x = c1.x * ratio + c2.x * (1 - ratio);
	r.y = c1.y * ratio + c2.y * (1 - ratio);
	r.z = c1.z * ratio + c2.z * (1 - ratio);
	return (t_vec3_color_to_int(r));
}
