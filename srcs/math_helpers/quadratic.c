/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:41:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/28 18:42:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

void	solve_quadratic(t_quadratic *q)
{
	q->discriminant = q->b * q->b - 4 * q->a * q->c;
	q->t1 = 1.0 / 0.0;
	q->t2 = 1.0 / 0.0;
	if (q->discriminant >= 0)
	{
		q->t1 = (-q->b + sqrt(q->discriminant)) / (2 * q->a);
		q->t2 = (-q->b - sqrt(q->discriminant)) / (2 * q->a);
	}
}
