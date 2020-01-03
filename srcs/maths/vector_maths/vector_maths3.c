/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:46:01 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/03 15:08:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double magnitude(t_vector3 a)
{
	return (distance(a, create_vector(0, 0, 0)));
}

double angle_between_vectors(t_vector3 a, t_vector3 b)
{
	double d;
	double angle;
	d = dot(a, b) / (magnitude(a) * magnitude(b));
	angle = acos(d);
	return (angle);
}

double dot_same(t_vector3 a)
{
	return (dot(a, a));
}

/*
** Apply rotation along x, y and z axis of base vector
** orientation values range from [-1.0;1.0]
** base vector is (1.0, 0.0, 0.0)
*/
t_vector3 apply_orientation(t_vector3 base, t_vector3 orient)
{
	t_vector3	ret;
	double		temp;
	double		angle;

	angle = orient.x * M_PI;
	ret.x = base.x;
	ret.y = base.y * cos(angle) - base.z * sin(angle);
	ret.z = base.y * sin(angle) + base.z * cos(angle);
	angle = orient.y * M_PI;
	temp = ret.x * cos(angle) + ret.z * sin(angle);
	ret.z = -ret.x * sin(angle) + ret.z * cos(angle);
	ret.x = temp;
	angle = orient.z * M_PI;
	temp = ret.x * cos(angle) - ret.y * sin(angle);
	ret.y = ret.x * sin(angle) + ret.y * cos(angle);
	ret.x = temp;
	return (ret);
}

t_vector3 rot_axis(t_vector3 axis, t_vector3 vec, double angle)
{
	t_vector3 rot;

	angle *= M_PI;
	rot = scalar_vect(vec, cos(angle));
	rot = add_vect(rot, scalar_vect(cross_prod(axis, vec), sin(angle)));
	return rot;
}
