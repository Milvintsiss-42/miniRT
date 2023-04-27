/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:43:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/04/27 17:05:50 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HELPERS_H
# define MATH_HELPERS_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_quadratic {
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	t_quadratic;

#endif
