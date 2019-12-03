/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:41:07 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/03 13:50:20 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>
int	raytrace_cyl(t_rt_param *param)
{
	t_vector3	abc;
	t_cylindre	*cyl;
	t_vector3	d_x_t;
	double		h;

	cyl = param->object;
	d_x_t.x = dot(param->ray, cyl->orient);
	d_x_t.y = dot(sub_vect(param->origin, cyl->centre), cyl->orient);
	abc.x = dot_same(param->ray) - pow(d_x_t.x, 2);
	abc.y = 2 * (dot(param->ray, sub_vect(param->origin, cyl->centre)) -
			d_x_t.x * d_x_t.y);
	abc.z = dot_same(sub_vect(param->origin, cyl->centre)) -
			pow(d_x_t.y, 2) - pow(cyl->diametre / 2, 2);
	if (!solve_quadratic(abc, &(param->i), &(param->i_2)))
		return (0);
	h = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		d_x_t.x * param->i;
	if (h > 0 && h < cyl->height)
		return (1);
	d_swap(&(param->i), &(param->i_2));
	h = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		d_x_t.x * param->i;
	if (h > 0 && h < cyl->height)
		return (1);
	return (0);
}

t_vector3 normal_vector_cyl(t_vector3 point, void *cyl)
{
	t_cylindre	*cy;
	double		h;
	t_vector3	a;

	cy = cyl;
	h = dot(sub_vect(point, cy->centre), cy->orient);
	a = point_from_ray(cy->centre, cy->orient, h);
	return (direction_vector(a, point));
}