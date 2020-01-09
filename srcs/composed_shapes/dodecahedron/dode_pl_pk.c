/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dode_pl_pk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:12:45 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 14:06:53 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>

void		make_dode_verts(double r, t_vector3 *vertices)
{
	double	g;
	int		i;

	i = 0;
	g = (1 + sqrt(5)) / 2.0;
	vertices[i++] = create_vector(r / sqrt(3), r / sqrt(3), r / sqrt(3));
	vertices[i++] = create_vector(r / sqrt(3), r / sqrt(3), -r / sqrt(3));
	vertices[i++] = create_vector(r / sqrt(3), -r / sqrt(3), -r / sqrt(3));
	vertices[i++] = create_vector(r / sqrt(3), -r / sqrt(3), r / sqrt(3));
	vertices[i++] = create_vector(-r / sqrt(3), -r / sqrt(3), r / sqrt(3));
	vertices[i++] = create_vector(-r / sqrt(3), -r / sqrt(3), -r / sqrt(3));
	vertices[i++] = create_vector(-r / sqrt(3), r / sqrt(3), -r / sqrt(3));
	vertices[i++] = create_vector(-r / sqrt(3), r / sqrt(3), r / sqrt(3));
}

void		make_dode_verts_2(t_vector3 centre, double r,
		t_vector3 *vertices, t_vector3 orient)
{
	double	g;
	int		i;

	i = 8;
	g = (1 + sqrt(5)) / 2.0;
	vertices[i++] = create_vector(0, r * g / sqrt(3), r / (g * sqrt(3)));
	vertices[i++] = create_vector(0, r * g / sqrt(3), -r / (g * sqrt(3)));
	vertices[i++] = create_vector(0, -r * g / sqrt(3), -r / (g * sqrt(3)));
	vertices[i++] = create_vector(0, -r * g / sqrt(3), r / (g * sqrt(3)));
	vertices[i++] = create_vector(r / (g * sqrt(3)), 0, r * g / sqrt(3));
	vertices[i++] = create_vector(r / (g * sqrt(3)), 0, -r * g / sqrt(3));
	vertices[i++] = create_vector(-r / (g * sqrt(3)), 0, -r * g / sqrt(3));
	vertices[i++] = create_vector(-r / (g * sqrt(3)), 0, r * g / sqrt(3));
	vertices[i++] = create_vector(r * g / sqrt(3), r / (g * sqrt(3)), 0);
	vertices[i++] = create_vector(r * g / sqrt(3), -r / (g * sqrt(3)), 0);
	vertices[i++] = create_vector(-r * g / sqrt(3), -r / (g * sqrt(3)), 0);
	vertices[i++] = create_vector(-r * g / sqrt(3), r / (g * sqrt(3)), 0);
	i = -1;
	while (++i < 20)
		vertices[i] = add_vect(apply_orientation(vertices[i], orient), centre);
}

t_vector3	get_penta_centre(t_vector3 p1, t_vector3 p2, t_vector3 p3, double r)
{
	double		vert_len;
	double		len;
	t_vector3	dir;
	t_vector3	center_plane;

	vert_len = 2 * r / (((1 + sqrt(5)) / 2.0) * sqrt(3));
	len = vert_len / (2 * sin(to_rad(36)));
	dir = normalise_vector(add_vect(direction_vector(p1, p2),
			scalar_vect(direction_vector(p2, p3), 0.5)));
	center_plane = point_from_ray(p1, dir, len);
	return (center_plane);
}

void		compute_dode_planes(t_vector3 *vert, t_vector3 *norm,
			double r, t_vector3 origin)
{
	int			i;
	t_vector3	center_plane;

	i = -1;
	center_plane = get_penta_centre(vert[0], vert[3], vert[17], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[0], vert[1], vert[9], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[2], vert[1], vert[16], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[2], vert[3], vert[11], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[0], vert[7], vert[15], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[1], vert[6], vert[14], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[2], vert[5], vert[14], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[3], vert[4], vert[15], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
}

void		compute_dode_planes_2(t_vector3 *vert, t_vector3 *norm,
			double r, t_vector3 origin)
{
	int			i;
	t_vector3	center_plane;

	i = 7;
	center_plane = get_penta_centre(vert[4], vert[7], vert[19], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[6], vert[7], vert[8], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[5], vert[6], vert[19], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[4], vert[5], vert[10], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
}
