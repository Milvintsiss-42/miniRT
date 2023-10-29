/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_basics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 22:29:21 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 22:35:18 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	precompute_cylinder_basics(t_cylinder *cylinder)
{
	cylinder->p_top_origin = vec3_sum(cylinder->origin,
			vec3_scal_prdct(cylinder->orientation, cylinder->height));
	cylinder->p_pow2_radius = pow(cylinder->diameter / 2, 2);
}

static void	precompute_sphere_basics(t_sphere *sphere)
{
	sphere->p_pow2_radius = pow(sphere->diameter / 2, 2);
}

void	precompute_basics(t_mrt	*mrt)
{
	t_l_obj	*obj_iter;

	obj_iter = mrt->scene.objects;
	while (obj_iter)
	{
		if (obj_iter->type == CYLINDER)
			precompute_cylinder_basics(obj_iter->object);
		else if (obj_iter->type == SPHERE)
			precompute_sphere_basics(obj_iter->object);
		obj_iter = obj_iter->next;
	}
}
