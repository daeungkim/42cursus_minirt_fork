/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 16:35:00 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/30 17:47:59 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	raytrace_plane(t_rt_param *param)
{
	t_plane *plane;
	double	t;

	plane = param->object;
	t = dot_prod(sub_vect(plane->centre, param->origin), plane->normal);
	t /= dot_prod(param->ray, plane->normal);
	if (t > 0)
	{
		param->intersection = t;
		return (1);
	}
	return (0);
}

t_vector3 normal_vector_plane(t_vector3 point, void *plane)
{
	t_plane	*pl;

	point.x = 0;
	pl = (t_plane *)plane;
	return (pl->normal);
}