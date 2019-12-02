/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:25:46 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 14:41:55 by cjaimes          ###   ########.fr       */
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

	*t1 = -1.0;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (0);
	if (disc == 0)
		*t0 = -abc.y / (2 * abc.x);
	else
	{
		q = -0.5 * (abc.y + ((abc.y > 0) ? sqrt(disc) : - sqrt(disc)));
		*t0 = q / abc.x;
		*t1 = abc.z / q;
		if (*t0 > *t1)
			*t0 = *t1;
		//add check to see if t is negative to prevent tracing objects behind camera
		if (*t0 < 0)
			return (0);
	}
	return (1);
}

int solve_square_boundaries(t_rt_param *param, t_square *square, double t)
{
	t_vector3	point;
	double		x_proj;
	double		z_proj;

	point = point_from_ray(param->origin, param->ray, t);
	point = direction_vector(point, square->centre);
	x_proj = dot_prod(point, square->x) / square->height;
	z_proj = dot_prod(point, square->z) / square->height;
	if ((x_proj < square->height && x_proj > 0) &&
		(z_proj < square->height && z_proj > 0))
		return (1);
	return (0);
}

int solve_disk_boundaries(t_rt_param *param, t_disk *disk, double t)
{
	t_vector3	point;
	double		dist;

	point = point_from_ray(param->origin, param->ray, t);
	dist = distance(point, disk->centre);
	if (dist < disk->diametre / 2)
		return (1);
	return (0);
}

double to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}
