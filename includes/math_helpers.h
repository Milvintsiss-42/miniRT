/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:43:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/05/31 20:32:40 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HELPERS_H
# define MATH_HELPERS_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_quadratic {
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	t_quadratic;

t_vec3		vec3_sum(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_diff(t_vec3 vec1, t_vec3 vec2);
double		vec3_magnitude(t_vec3 vec);
t_vec3		vec3_normalize(t_vec3 vec);
double		vec3_dot_prdct(t_vec3 vec1, t_vec3 vec2);
t_vec3		vec3_scal_prdct(t_vec3 vec, double scalar);
t_vec3		vec3_cross_prdct(t_vec3 vec1, t_vec3 vec2);
double		vec3_ang_btwn(t_vec3 vec1, t_vec3 vec2);

#endif
