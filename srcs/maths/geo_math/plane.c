/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 16:35:00 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:17:59 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			raytrace_plane(t_rt_param *param)
{
	t_plane *plane;
	double	t;
	double	denom;

	plane = param->object;
	t = dot(sub_vect(plane->centre, param->origin), plane->normal);
	denom = dot(param->ray, plane->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (0);
	t /= denom;
	param->i = t;
	if (t > 0)
		return ((param->v = 1));
	return (0);
}

t_vector3	normal_vector_plane(t_vector3 point, void *plane)
{
	t_plane	*pl;

	point.x = 0;
	pl = (t_plane *)plane;
	return (pl->normal);
}
