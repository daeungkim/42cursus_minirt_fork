/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_maths_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:01:32 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/13 15:08:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_geo	*check_reflection(t_data *d, t_geo *hit_obj)
{
	t_vector3 norm;

	d->ref_lvl++;
	d->ray_origin = point_from_ray(d->ray_origin, d->ray, d->t);
	norm = get_normal_vector(d->ray_origin, hit_obj, d);
	d->ray_origin = add_vect(d->ray_origin, scalar_vect(norm, 0.001));
	d->ray = reflect_vector(d->ray, norm);
	d->t = -1.0;
	return (find_closest_hit(d));
}

t_geo	*check_refraction(t_data *d, t_geo *hit_obj)
{
	t_vector3 norm;

	d->has_ref = 1;
	d->out = d->out ? 0 : 1;
	d->ray_origin = point_from_ray(d->ray_origin, d->ray, d->t);
	norm = get_normal_vector(d->ray_origin, hit_obj, d);
	d->ray_origin = add_vect(d->ray_origin, scalar_vect(norm, -0.0001));
	d->ray = refract_vector(d->ray, norm, d);
	d->t = -1.0;
	return (find_closest_hit(d));
}
