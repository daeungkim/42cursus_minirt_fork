/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:35:14 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/13 10:51:30 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			raytrace(t_geo *geo, t_rt_param *param)
{
	param->object = geo->obj;
	if (geo->find_inter(param))
		return (1);
	return (0);
}

t_vector3	get_normal_vector(t_vector3 point, t_geo *geo, t_data *d)
{
	t_vector3 normal;

	normal = geo->get_normal_vector(point, geo->obj);
	if (dot(normal, d->ray) > 0)
		normal = scalar_vect(normal, -1.0);
	return (normalise_vector(normal));
}
