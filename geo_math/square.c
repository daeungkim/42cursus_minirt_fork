/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:06:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 12:35:56 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	raytrace_square(t_rt_param *param)
{
	t_square	*square;
	double		t;
	double		denom;
	t_vector3	v;
	double		x_proj;
	double		z_proj;

	square = param->object;
	t = dot_prod(sub_vect(square->centre, param->origin), square->normal);
	denom = dot_prod(param->ray, square->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (0);
	t /= denom;
	param->i = t;
	if (t > 0)
	{
		v = point_from_ray(param->origin, param->ray, t);
		v = direction_vector(v, square->centre);
		x_proj = dot_prod(v, square->x) / square->height;
		z_proj = dot_prod(v, square->z) / square->height;
		if ((x_proj < square->height && x_proj > 0) &&
			(z_proj < square->height && z_proj > 0))
			return (1);
	}
	return (0);
}

t_vector3 normal_vector_square(t_vector3 point, void *square)
{
	t_square	*sq;

	point.x = 0;
	sq = (t_square *)square;
	return (sq->normal);
}