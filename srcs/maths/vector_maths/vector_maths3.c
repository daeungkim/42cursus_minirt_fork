/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:46:01 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 18:40:38 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double magnitude(t_vector3 a)
{
	return (distance(a, create_vector(0, 0, 0)));
}

double angle_between_vectors(t_vector3 a, t_vector3 b)
{
	double dot;
	double angle;
	dot = dot_prod(a, b) / (magnitude(a) * magnitude(b));
	angle = acos(dot);
	return (angle);
}

double dot_same(t_vector3 a)
{
	return (dot_prod(a, a));
}