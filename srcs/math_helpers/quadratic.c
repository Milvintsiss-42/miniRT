/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:41:48 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/30 20:38:51 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_helpers.h"

/// @brief Solves the quadratic equation `a * t² + b * t + c = 0` and stores the
/// result in [q]. [q.a], [q.b] and [q.c] need to be set before calling this
/// function.
/// If the discriminant is negative, [q.t1] and [q.t2] are set to inf.
/// If the discriminant is 0, [q.t1] and [q.t2] are set to the same value.
/// If the discriminant is positive, [q.t1] and [q.t2] are set to the 2
/// solutions of the equation.
/// @param q
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
