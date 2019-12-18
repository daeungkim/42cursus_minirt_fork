/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:15:01 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/18 11:22:03 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>
int raytrace_torus(t_rt_param *par)
{
	t_quartic	q;
	t_vector3	o;
	int 		sol;
	t_orus *t;

	t = par->object;

	o = sub_vect(par->origin, t->centre);
	q.a = pow(dot_same(par->ray), 2);
	q.b = 4 * dot_same(par->ray) * dot(par->ray, o) / q.a;
	q.c = (4 * q.a + 2 * dot_same(par->ray) * dot_same(o) -
		2 * (pow(t->i_dia, 2) + pow(t->o_dia, 2)) * dot_same(par->ray) +
		4 * pow(t->o_dia, 2) * pow(dot(par->ray, t->normal), 2)) / q.a;
	q.d = (4 * dot(par->ray, o) * dot_same(o) -
		4 * (pow(t->i_dia, 2) + pow(t->o_dia, 2)) * dot(par->ray, o) +
		8 * pow(t->o_dia, 2) * dot(par->ray, t->normal) * dot(o, t->normal)) / 
		q.a;
	q.e = (pow(dot_same(o), 2) -
		2 * (pow(t->i_dia, 2) + pow(t->o_dia, 2)) * dot_same(o) +
		4 * pow(t->o_dia, 2) * pow(dot(o, t->normal), 2) +
		pow(pow(t->i_dia, 2) - pow(t->o_dia, 2), 2)) / q.a;
	sol = solve_quartic(q, par);
	if (sol >= 2)
	{
		par->v = 1;
		par->v_2 = 1;
		if (par->i > par->i_2)
			d_swap(&(par->i), &(par->i_2));
		if (sol == 4)
		{
			par->v_3 = 1;
			par->v_4 = 1;	
		}
	}
	return (sol);
}


t_vector3 normal_vector_torus(t_vector3 point, void *tor)
{
	t_orus	*t;
	double		k;
	double		m;
	t_vector3	a;

	t = tor;
	k = dot(sub_vect(point, t->centre), t->normal);
	a = point_from_ray(point, t->normal, -k);
	m = sqrt(t->i_dia * t->i_dia - k * k);
	return (sub_vect(
		direction_vector(a, point),
		scalar_vect(sub_vect(t->centre, a), m / (t->o_dia + m))));
}