/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:25:46 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/06 12:47:20 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>
/*
** To avoid catastrophic cancellation between b and discriminant,
** we will use a sign function
*/
int solve_quadratic(t_vector3 abc, double *t0, double *t1)
{
	double disc;
	double q;
	double temp;

	*t1 = -1.0;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (0);
	if (disc == 0)
	{
		*t0 = -abc.y / (2 * abc.x);
		return (1);
	}
	q = -0.5 * (abc.y + ((abc.y > 0) ? sqrt(disc) : - sqrt(disc)));
	*t0 = q / abc.x;
	*t1 = abc.z / q;
	temp = *t0;
	if (*t0 > *t1)
	{
		*t0 = *t1;
		*t1 = temp;
	}
	return (2);
}

int solve_square_boundaries(t_rt_param *param, t_square *square)
{
	t_vector3	point;
	double		x_proj;
	double		z_proj;

	point = point_from_ray(param->origin, param->ray, param->i);
	point = direction_vector(point, square->centre);
	x_proj = dot(point, square->x) / square->height;
	z_proj = dot(point, square->z) / square->height;
	if ((x_proj < square->height && x_proj > 0) &&
		(z_proj < square->height && z_proj > 0))
		return (1);
	return (0);
}

int solve_disk_boundaries(t_rt_param *param, t_disk *disk)
{
	t_vector3	point;
	double		dist;

	point = point_from_ray(param->origin, param->ray, param->i);
	dist = distance(point, disk->centre);
	if (dist < disk->diametre / 2)
		return (1);
	return (0);
}

int solve_triangle_boundaries(t_rt_param *param, t_triangle *tri)
{
    t_vector3 inter;
    t_vector3 edge;
    t_vector3 vertice_inter;

    inter = point_from_ray(param->origin, param->ray, param->i);
    edge = direction_vector(tri->p1, tri->p2);
    vertice_inter = direction_vector(tri->p1, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    edge = direction_vector(tri->p2, tri->p3);
    vertice_inter = direction_vector(tri->p2, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    edge = direction_vector(tri->p3, tri->p1);
    vertice_inter = direction_vector(tri->p3, inter);
    if (dot(tri->normal, cross_prod(edge, vertice_inter)) > 0)
        return (0);
    return (1);
}
