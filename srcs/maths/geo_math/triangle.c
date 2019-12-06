/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:33:32 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/05 19:35:55 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>
t_vector3 define_tri_plane(t_vector3 p1, t_vector3 p2, t_vector3 p3)
{
    t_vector3 ab;
    t_vector3 ac;

    ab = direction_vector(p1, p2);
    ac = direction_vector(p1, p3);
    return (normalise_vector(cross_prod(ab, ac)));
}

int	raytrace_triangle(t_rt_param *param)
{
	t_triangle	*tri;
	double		t;
	double		denom;

	tri = param->object;
	t = dot(sub_vect(tri->p1, param->origin), tri->normal);
	denom = dot(param->ray, tri->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (0);
	param->i = t / denom;
	if (param->i > 0)
        if (solve_triangle_boundaries(param, tri))
            return ((param->v = 1));
	return (0);
}

t_vector3 normal_vector_triangle(t_vector3 point, void *triangle)
{
	t_triangle	*tr;

	point.x = 0;
	tr = (t_triangle *)triangle;
	return (tr->normal);
}