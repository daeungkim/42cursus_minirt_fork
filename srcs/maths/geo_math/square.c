/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:06:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 15:24:28 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	raytrace_square(t_rt_param *param)
{
	t_square	*square;
	double		t;
	double		denom;

	square = param->object;
	t = dot_prod(sub_vect(square->centre, param->origin), square->normal);
	denom = dot_prod(param->ray, square->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (0);
	param->i = t / denom;
	if (param->i > 0)
		if (solve_square_boundaries(param, square))
			return (1);
	return (0);
}

t_vector3 normal_vector_square(t_vector3 point, void *square)
{
	t_square	*sq;

	point.x = 0;
	sq = (t_square *)square;
	return (sq->normal);
}