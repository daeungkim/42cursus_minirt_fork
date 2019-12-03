/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:35:22 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/04 00:31:43 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** ray can be expressed with R = O + Dt with O being camera coordinates
** and D its normalised orientation vector
*/
int	raytrace_sphere(t_rt_param *param)
{
	t_vector3	abc;
	t_sphere	*sp;
	double		t0;
	double		t1;

	sp = param->object;
	abc.x = dot(param->ray, param->ray);
	abc.y = 2 * dot(param->ray, sub_vect(param->origin, sp->centre));
	abc.z = dot(sub_vect(param->origin, sp->centre),
				sub_vect(param->origin, sp->centre)) -
				(sp->diametre * (sp->diametre / 4.0));
	if (!solve_quadratic(create_vector(abc.x, abc.y, abc.z), &t0, &t1))
		return (0);
	if (t0 < 0)
		return (0);
	param->i = t0;
	return (1);
}

t_vector3 normal_vector_sphere(t_vector3 point, void *sphere)
{
	t_vector3 normal;
	t_sphere	*sp;

	sp = (t_sphere *)sphere;
	normal = direction_vector(sp->centre, point);
	return (normal);
}
