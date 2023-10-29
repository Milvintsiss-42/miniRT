/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:20:54 by ple-stra          #+#    #+#             */
/*   Updated: 2023/10/29 22:38:23 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static t_vec3	light_direction(t_obj_type light_type, t_light light, t_point p)
{
	if (light_type == SPOT_LIGHT)
		return (vec3_diff(light.origin_o_dir, p.p));
	else if (light_type == DIR_LIGHT)
		return (light.origin_o_dir);
	return ((t_vec3){0, 0, 0});
}

static bool	is_in_shadow(t_mrt *mrt, t_point p, t_l_obj light)
{
	t_intersect	clst_inter;
	double		t_max;
	bool		is_flag_light_v_active;

	t_max = 0.0;
	if (light.type == SPOT_LIGHT)
		t_max = 1.0;
	else if (light.type == DIR_LIGHT)
		t_max = __DBL_MAX__;
	is_flag_light_v_active = ft_checkflag(mrt->event_mode.flags, FLAG_LIGHT_V);
	ft_resetflag(&mrt->event_mode.flags, FLAG_LIGHT_V);
	clst_inter = closest_intersection(mrt, (t_ray){p.p, p.l, LOW_DBL, t_max});
	if (is_flag_light_v_active)
		ft_setflag(&mrt->event_mode.flags, FLAG_LIGHT_V);
	return (clst_inter.obj != NULL);
}

static double	compute_diffuse_light(t_point *p, t_light light)
{
	if (vec3_dot_prdct(p->n, p->l) > 0)
		return (light.brightness * vec3_dot_prdct(p->n, p->l)
			/ (vec3_magnitude(p->n) * vec3_magnitude(p->l)));
	return (0.0);
}

static double	compute_specular_light(t_point *p, t_light light)
{
	double	r_dot_v;

	if (p->s == -1)
		return (0.0);
	p->r = reflect_ray(p->l, p->n);
	r_dot_v = vec3_dot_prdct(p->r, p->v);
	if (r_dot_v > 0)
		return (light.brightness
			* pow(r_dot_v / (vec3_magnitude(p->r) * vec3_magnitude(p->v)),
				p->s));
	return (0.0);
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
	double	brightness;

	l_lights = mrt->scene.lights;
	p->b = brightness_color_wise(mrt->scene.amb_light.brightness,
			mrt->scene.amb_light.color);
	while (l_lights)
	{
		brightness = 0;
		light = (t_light)(*(t_light *)(l_lights->object));
		p->l = light_direction(l_lights->type, light, *p);
		if (is_in_shadow(mrt, *p, *l_lights))
		{
			l_lights = l_lights->next;
			continue ;
		}
		brightness += compute_diffuse_light(p, light);
		brightness += compute_specular_light(p, light);
		p->b = vec3_sum(p->b, brightness_color_wise(brightness, light.color));
		l_lights = l_lights->next;
	}
	p->b.x = ft_min_d(p->b.x, 1.0);
	p->b.y = ft_min_d(p->b.y, 1.0);
	p->b.z = ft_min_d(p->b.z, 1.0);
}
