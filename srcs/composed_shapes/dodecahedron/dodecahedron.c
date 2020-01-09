/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dodecahedron.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:47:49 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 14:07:50 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>

void	compute_peaks(t_vector3 *planes, t_vector3 *peaks,
		double r, t_vector3 origin)
{
	int i;

	i = -1;
	while (i++ < 12)
		peaks[i] = point_from_ray(origin, planes[i], r * 2);
}

t_list	*create_dodecahedron(double radius, t_vector3 orient,
		t_vector3 centre, int colour)
{
	t_vector3	v[20];
	t_vector3	n[12];
	t_vector3	p[12];
	t_list		*ele;
	t_list		*new;

	ele = 0;
	make_dode_verts(radius, v);
	make_dode_verts_2(centre, radius, v, orient);
	compute_dode_planes(v, n, radius, centre);
	compute_dode_planes_2(v, n, radius, centre);
	compute_peaks(n, p, radius, centre);
	if (!(new = generate_tri_1_5(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_tri_6_10(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	if (!(new = generate_tri_11_12(v, p, colour)))
		return (0);
	ft_lstadd_back(&ele, new);
	return (ele);
}
