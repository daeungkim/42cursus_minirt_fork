/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:41:07 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/16 16:17:15 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

static int check_cyl_solve(t_rt_param *param, t_cylindre *cyl)
{
	t_vector3	d_x_t;
	t_vector3	abc;
	int 		sol;

	d_x_t.x = dot(param->ray, cyl->orient);
	d_x_t.y = dot(sub_vect(param->origin, cyl->centre), cyl->orient);
	abc.x = dot_same(param->ray) - pow(d_x_t.x, 2);
	abc.y = 2 * (dot(param->ray, sub_vect(param->origin, cyl->centre)) -
			d_x_t.x * d_x_t.y);
	abc.z = dot_same(sub_vect(param->origin, cyl->centre)) -
			pow(d_x_t.y, 2) - pow(cyl->diametre / 2, 2);
	sol = solve_quadratic(abc, &(param->i), &(param->i_2));
	if (sol >= 1)
		param->v = 1;
	if (sol == 2)
		param->v_2 = 1;
	return (sol);
}

int	raytrace_cyl(t_rt_param *param)
{
	t_cylindre	*cyl;
	double		h1;
	double		h2;

	cyl = param->object;
	if (!check_cyl_solve(param, cyl))
		return (0);
	h1 = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		dot(param->ray, cyl->orient) * param->i;
	if (h1 < 0 || h1 > cyl->height)
		param->v = 0;
	h2 = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		dot(param->ray, cyl->orient) * param->i_2;
	if (h2 < 0 || h2 > cyl->height)
		param->v_2 = 0;
	return ((param->v && h1 < cyl->height) ||
			(param->v_2 && h2 < cyl->height));
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