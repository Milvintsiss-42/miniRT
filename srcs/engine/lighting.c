/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:20:54 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/09 08:10:27 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	compute_specular_light(t_point *p, t_light light)
{
	double	r_dot_v;

	p->r = reflect_ray(p->l, p->n);
	r_dot_v = vec3_dot_prdct(p->r, p->v);
	if (r_dot_v > 0)
		p->b += light.brightness
			* pow(r_dot_v / (vec3_magnitude(p->r) * vec3_magnitude(p->v)),
				p->s);
}

static bool	is_in_shadow(t_mrt *mrt, t_point p, t_l_obj light)
{
	t_intersect	clst_inter;
	double		t_max;

	t_max = 0.0;
	if (light.type == SPOT_LIGHT)
		t_max = 1.0;
	else if (light.type == DIR_LIGHT)
		t_max = __DBL_MAX__;
	clst_inter = closest_intersection(mrt, p.p, p.l, 0.0000001, t_max);
	if (!clst_inter.obj)
		return (false);
	return (true);
}

/// @brief Computes the brightness of a point, based on the ambient light and
/// the lights in the scene.
/// @param mrt
/// @param p The struct containing the informations about the point which
/// brightness is being computed.
/// [p] is the position of the point to compute the brightness of.
/// [n] is the direction of the object's normal at the point.
/// [v] is the direction from the point to the camera.
/// [s] is the specular exponant of the object.
/// [b], [l] and [r] can be leave empty, they are only used during calculations.
/// [l] is the direction of the light from the point to a light.
/// [r] is the direction of the reflected light from the point.
/// [b] is the computed brightness at the point.
/// @return Does not return anything. The computed brightness is stored in
/// [p->b].
void	compute_lighting(t_mrt *mrt, t_point *p)
{
	t_l_obj	*l_lights;
	t_light	light;

	l_lights = mrt->scene.lights;
	p->b = mrt->scene.amb_light.brightness;
	while (l_lights)
	{
		light = (t_light)(*(t_light *)(l_lights->object));
		if (l_lights->type == SPOT_LIGHT)
			p->l = vec3_diff(light.origin_o_dir, p->p);
		else if (l_lights->type == DIR_LIGHT)
			p->l = light.origin_o_dir;
		if (is_in_shadow(mrt, *p, *l_lights))
		{
			l_lights = l_lights->next;
			continue ;
		}
		if (vec3_dot_prdct(p->n, p->l) > 0)
			p->b += light.brightness * vec3_dot_prdct(p->n, p->l)
				/ (vec3_magnitude(p->n) * vec3_magnitude(p->l));
		if (p->s != -1)
			compute_specular_light(p, light);
		l_lights = l_lights->next;
	}
	p->b = ft_min_d(p->b, 1.0);
}
