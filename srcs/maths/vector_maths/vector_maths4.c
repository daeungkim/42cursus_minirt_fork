/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:44:20 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/13 15:10:11 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector3	reflect_vector(t_vector3 ray, t_vector3 normal)
{
	return (sub_vect(ray, scalar_vect(normal, 2 * dot(ray, normal))));
}

t_vector3	refract_vector(t_vector3 ray, t_vector3 normal, t_data *d)
{
	t_vector3	new;
	double		index;
	double		c1;
	double		c2;

	index = d->out ? 1.0 / 1.5 : 1.0 / 1.5;
	if (!d->out)
		scalar_vect(normal, -1.0);
	c1 = dot(normal, ray);
	c2 = sqrt(1 - index * index * (1 - c1 * c1));
	new = scalar_vect(add_vect(ray, scalar_vect(normal, c1)), index);
	new = sub_vect(new, scalar_vect(normal, c2));
	return (new);
}
