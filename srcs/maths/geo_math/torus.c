/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:15:01 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/22 21:16:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>
int raytrace_torus1(t_rt_param *par)
{
	t_quartic	q;
	t_vector3	o;
	int 		sol;
	t_orus *t;

	t = par->object;

	o = sub_vect(par->origin, t->centre);
	double a = 1 - pow(dot(par->ray, t->normal), 2);
	double b = 2 * (dot(o, par->ray) - dot(t->normal, o) * dot(t->normal, par->ray));
	double c = dot_same(o) - dot(t->normal, o) * dot(t->normal, par->ray);
	double d = dot_same(o) + pow(t->o_dia, 2) - pow(t->i_dia, 2);
	q.a = 1;
	q.b = 4 * dot(par->ray, o);
	q.c = 2 * d + q.b * q.b * 0.25 - 4 * pow(t->o_dia, 2) * a;
	q.d = q.b * d - 4 * pow(t->o_dia, 2) * b;
	q.e = d * d - 4 * pow(t->o_dia, 2) * c;
	sol = solve_quartic(q, par);
	//printf("a = %g | b = %g | c = %g | d = %g | e = %g\n", q.a, q.b, q.c, q.d, q.e);
	//printf("%d real solutions\n",sol);
	// if (par->v && par->v_2)
    //     printf("1st root = %g\n2nd root = %g\n", par->i, par->i_2);
    // if (par->v_3 && par->v_4)
    //     printf("1st root = %g\n2nd root = %g\n", par->i_3, par->i_4);
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
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i_3 > par->i_4)
				d_swap(&(par->i_3), &(par->i_4));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
		}
	}
	return (sol);
}

int raytrace_torus(t_rt_param *par)
{
	t_quartic	q;
	int 		sol;
	t_orus *t;

	t = par->object;

	t_vector3 x = sub_vect(par->origin, t->centre);
	double dx = dot(par->ray, x);
	double xv = dot(x, t->normal);
	double xx = dot_same(x);
	double dv = dot(par->ray, t->normal);
	double Rr = t->o_dia * t->o_dia - t->i_dia * t->i_dia;


	q.a = 1;
	q.b = 4 * dx;
	q.c = 4 * dx * dx + 2 * xx + 2 * Rr - 4 * t->o_dia * t->o_dia * (1 - dv * dv);
	q.d = 4 * dx * xx + 4 * Rr * dx - 8 * t->o_dia * t->o_dia * (dx - dv * xv);
	q.e = xx * xx + Rr * Rr + 2 * Rr * xx - 4 * t->o_dia * t->o_dia * (xx - xv * xv);

	// find roots of the quartic equation

	sol = solve_quartic(q, par);
	
	if (sol == 0)  // ray misses the torus
		return(0);

	//printf("a = %g | b = %g | c = %g | d = %g | e = %g\n", q.a, q.b, q.c, q.d, q.e);
	//printf("%d real solutions\n",sol);
	// if (par->v && par->v_2)
    //     printf("1st root = %g\n2nd root = %g\n", par->i, par->i_2);
    // if (par->v_3 && par->v_4)
    //     printf("1st root = %g\n2nd root = %g\n", par->i_3, par->i_4);
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
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i_3 > par->i_4)
				d_swap(&(par->i_3), &(par->i_4));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
			if (par->i_2 > par->i_3)
				d_swap(&(par->i_2), &(par->i_3));
			if (par->i > par->i_2)
				d_swap(&(par->i), &(par->i_2));
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