/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:15:01 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/10 17:24:21 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

static void	fill_params(t_quartic *q, t_orus *t, t_rt_param *par, t_vector3 x)
{
	double dx;
	double xv;
	double xx;
	double dv;
	double rr;

	dx = dot(par->ray, x);
	xv = dot(x, t->normal);
	xx = dot_same(x);
	dv = dot(par->ray, t->normal);
	rr = t->o_dia * t->o_dia - t->i_dia * t->i_dia;
	q->a = 1;
	q->b = 4 * dx;
	q->c = 4 * dx * dx + 2 * xx + 2 * rr - 4 *
			t->o_dia * t->o_dia * (1 - dv * dv);
	q->d = 4 * dx * xx + 4 * rr * dx - 8 * t->o_dia *
			t->o_dia * (dx - dv * xv);
	q->e = xx * xx + rr * rr + 2 * rr * xx - 4 * t->o_dia *
			t->o_dia * (xx - xv * xv);
}

int			raytrace_torus(t_rt_param *par)
{
	t_quartic	q;
	int			sol;
	t_orus		*t;
	t_vector3	x;

	t = par->object;
	x = sub_vect(par->origin, t->centre);
	fill_params(&q, t, par, x);
	sol = solve_quartic(q, par);
	return (sol);
}

t_vector3	normal_vector_torus(t_vector3 point, void *tor)
{
	t_orus		*t;
	double		k;
	t_vector3	a;
	t_vector3	pr;

	t = tor;
	k = dot(sub_vect(point, t->centre), t->normal);
	a = point_from_ray(point, t->normal, -k);
	pr = normalise_vector(sub_vect(a, t->centre));
	pr = point_from_ray(t->centre, pr, t->o_dia);
	return (direction_vector(pr, point));
}
