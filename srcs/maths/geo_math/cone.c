/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:15:01 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/03 15:07:37 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int check_cone_solve(t_rt_param *param, t_cone *cone)
{
	t_vector3	d_x_t;
	t_vector3	abc;
	double		k;
	int 		sol;

	k = cone->diametre / (2.0 * cone->height);
	d_x_t.x = dot(param->ray, cone->normal);
	d_x_t.y = dot(sub_vect(param->origin, cone->centre), cone->normal);
	abc.x = dot_same(param->ray) - pow(d_x_t.x, 2) * (1 + pow(k, 2));
	abc.y = 2 * (dot(param->ray, sub_vect(param->origin, cone->centre)) -
			d_x_t.x * d_x_t.y * (1 + pow(k, 2)));
	abc.z = dot_same(sub_vect(param->origin, cone->centre)) -
			pow(d_x_t.y, 2) * (1 + pow(k, 2));
	sol = solve_quadratic(abc, &(param->i), &(param->i_2));
	if (sol >= 1)
		param->v = 1;
	if (sol == 2)
		param->v_2 = 1;
	return (sol);
}

int	raytrace_cone(t_rt_param *param)
{
	t_cone	*cone;
	double		h1;
	double		h2;

	cone = param->object;
	if (!check_cone_solve(param, cone))
		return (0);
	h1 = dot(sub_vect(param->origin, cone->centre), cone->normal) +
		dot(param->ray, cone->normal) * param->i;
	if (h1 < 0 || h1 > cone->height)
		param->v = 0;
	h2 = dot(sub_vect(param->origin, cone->centre), cone->normal) +
		dot(param->ray, cone->normal) * param->i_2;
	if (h2 < 0 || h2 > cone->height)
		param->v_2 = 0;
	return ((param->v && h1 < cone->height) ||
			(param->v_2 && h2 < cone->height));
}

t_vector3 normal_vector_cone(t_vector3 point, void *con)
{
	t_cone		*cone;
	double		h;
	double		k;
	t_vector3	a;

	cone = con;
	k = cone->diametre / (2.0 * cone->height);
	h = dot(sub_vect(point, cone->centre), cone->normal);
	a = point_from_ray(cone->centre, cone->normal, h * (1 + pow(k, 2)));
	return (direction_vector(a, point));
}