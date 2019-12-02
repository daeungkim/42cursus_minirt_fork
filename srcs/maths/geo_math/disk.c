/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:21:06 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/02 15:22:50 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	raytrace_disk(t_rt_param *param)
{
	t_disk	*disk;
	double	t;
	double	denom;

	disk = param->object;
	t = dot_prod(sub_vect(disk->centre, param->origin), disk->normal);
	denom = dot_prod(param->ray, disk->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (0);
	param->i = t / denom;
	if (param->i > 0)
		if (solve_disk_boundaries(param, disk))
			return (1);
	return (0);
}

t_vector3 normal_vector_disk(t_vector3 point, void *disk)
{
	t_disk	*dk;

	point.x = 0;
	dk = (t_disk *)disk;
	return (dk->normal);
}