/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:12:25 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/30 19:26:22 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector3 point_from_ray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}

/*
** Returns a vector with a direction set by points a and b
** (vector going from a to b)
*/
t_vector3 direction_vector(t_vector3 a, t_vector3 b)
{
	b.x -= a.x;
	b.y -= a.y;
	b.z -= a.z;
	return (b);
}

/*
** Returns a vector with a length of 1
*/
t_vector3 normalise_vector(t_vector3 v)
{
	double		dist;
	t_vector3	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	dist = distance(v, origin);
	v.x /= dist;
	v.y /= dist;
	v.z /= dist;
	return (v);
}

/*
** This gives ||a|| * cos(theta), theta being the angle between a and b
*/
double dot_prod(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
** cross product returns a vector perpendicular to vectors a and b
*/
t_vector3 cross_prod(t_vector3 a, t_vector3 b)
{
	t_vector3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}