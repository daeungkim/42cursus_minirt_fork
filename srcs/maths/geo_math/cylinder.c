/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:41:07 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 19:48:15 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	raytrace_cyl(t_rt_param *param)
{
	t_vector3	abc;
	t_cylindre	*cyl;
	double		dv;
	double		xv;
	double		t1;
	double		h;

	cyl = param->object;
	dv = dot_prod(param->ray, cyl->orient);
	xv = dot_prod(sub_vect(param->origin, cyl->centre), cyl->orient);
	abc.x = dot_same(param->ray) - pow(dv, 2);
	abc.y = 2 * (dot_prod(param->ray, sub_vect(param->origin, cyl->centre)) -
			dv * xv);
	abc.z = dot_same(sub_vect(param->origin, cyl->centre)) -
			pow(xv, 2) - pow(cyl->diametre / 2, 2);
	if (!solve_quadratic(create_vector(abc.x, abc.y, abc.z), &(param->i), &t1))
		return (0);
	h = dot_prod(sub_vect(param->origin, cyl->centre), cyl->orient) +
		dv * param->i;
	if (h > 0 && h < cyl->height)
		return (1);
	return (0);
}

double get_h(double t, t_vector3 point, t_cylindre *cyl)
{
	double h;

	h = dot_prod(sub_vect(point, cyl->centre), cyl->orient);
}
WIP
t_vector3 normal_vector_cyl(t_vector3 point, void *cyl)
{
	t_cylindre *cy;
	double h;

	cy = cyl
	h = dot_prod(sub_vect(point, cyl->centre), cyl->orient);
	return (direction_vector());
}