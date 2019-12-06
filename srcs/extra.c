/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:47:49 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/07 00:21:34 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>

void make_dodecahedron(t_vector3 centre, double r, t_vector3 *vertices, t_vector3 orient)
{
	double g;
	int i;

	i = 0;
	g = (1 + sqrt(5)) / 2.0;
	// 1 2 5
	vertices[i++] = create_vector(r / sqrt(3), r / sqrt(3), r / sqrt(3));
	// 2 3 6
	vertices[i++] = create_vector(r / sqrt(3), r / sqrt(3), -r / sqrt(3));
	// 3 4 7
	vertices[i++] = create_vector(r / sqrt(3), -r / sqrt(3), -r / sqrt(3));
	// 4 1 8
	vertices[i++] = create_vector(r / sqrt(3), -r / sqrt(3), r / sqrt(3));
	// 12 9 8
	vertices[i++] = create_vector(-r / sqrt(3), -r / sqrt(3), r / sqrt(3));
	// 11 12 7
	vertices[i++] = create_vector(-r / sqrt(3), -r / sqrt(3), -r / sqrt(3));
	// 10 11 6
	vertices[i++] = create_vector(-r / sqrt(3), r / sqrt(3), -r / sqrt(3));
	// 9 10 5
	vertices[i++] = create_vector(-r / sqrt(3), r / sqrt(3), r / sqrt(3));

	// 2 5 10    8 
	vertices[i++] = create_vector(0, r * g / sqrt(3), r / (g * sqrt(3)));
	// 2 6 10
	vertices[i++] = create_vector(0, r * g / sqrt(3), -r / (g * sqrt(3)));
	// 4 7 12
	vertices[i++] = create_vector(0, -r * g / sqrt(3), -r / (g * sqrt(3)));
	// 4 8 12
	vertices[i++] = create_vector(0, -r * g / sqrt(3), r / (g * sqrt(3)));

	// 1 5 8     12
	vertices[i++] = create_vector(r / (g * sqrt(3)), 0, r * g / sqrt(3));
	// 3 6 7
	vertices[i++] = create_vector(r / (g * sqrt(3)), 0, -r * g / sqrt(3));
	// 11 6 7
	vertices[i++] = create_vector(-r / (g * sqrt(3)), 0, -r * g / sqrt(3));
	// 9 5 8
	vertices[i++] = create_vector(-r / (g * sqrt(3)), 0, r * g / sqrt(3));

	// 1 2 3     16
	vertices[i++] = create_vector(r * g / sqrt(3), r / (g * sqrt(3)), 0);
	// 1 3 4
	vertices[i++] = create_vector(r * g / sqrt(3), -r / (g * sqrt(3)), 0);
	// 9 11 12
	vertices[i++] = create_vector(-r * g / sqrt(3), -r / (g * sqrt(3)), 0);
	// 9 10 11
	vertices[i++] = create_vector(-r * g / sqrt(3), r / (g * sqrt(3)), 0);
	i = -1;

	
	while (++i < 20)
		vertices[i] = add_vect(apply_orientation(vertices[i], orient), centre);

}

t_vector3 get_penta_centre(t_vector3 p1, t_vector3 p2, t_vector3 p3, double r)
{
	double vert_len;
	double len;
	t_vector3 dir;
	t_vector3 center_plane;

	vert_len = 2 * r / (((1 + sqrt(5)) / 2.0) * sqrt(3));
	len = vert_len / (2 * sin(to_rad(36)));
	dir = normalise_vector(add_vect(direction_vector(p1, p2),
			scalar_vect(direction_vector(p2, p3), 0.5)));
	center_plane = point_from_ray(p1, dir, len);
	return (center_plane);
}

void compute_dode_planes(t_vector3 *vert, t_vector3 *norm, double r, t_vector3 origin)
{
	int i;
	t_vector3 center_plane;

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

	center_plane = get_penta_centre(vert[4], vert[7], vert[19], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[6], vert[7], vert[8], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[5], vert[6], vert[19], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
	center_plane = get_penta_centre(vert[4], vert[5], vert[10], r);
	norm[++i] = normalise_vector(direction_vector(origin, center_plane));
}

void	compute_peaks(t_vector3 *planes, t_vector3 *peaks, double r, t_vector3 origin)
{
	int i;

	i = -1;
	while (i++ < 12)
		peaks[i] = point_from_ray(origin, planes[i], r * 2);
}

void generate_triangles(t_vector3 *vert, t_vector3 *peaks, t_data *data, int colour)
{
	t_list *ele;
	colour = 0;
	ele = ft_lstnew(tri_factory(peaks[0], vert[0], vert[16], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[0], vert[0], vert[12], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[0], vert[3], vert[17], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[0], vert[3], vert[12], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[0], vert[17], vert[16], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[1], vert[0], vert[16], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[1], vert[0], vert[8], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[1], vert[8], vert[9], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[1], vert[9], vert[1], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[1], vert[1], vert[0], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[2], vert[17], vert[16], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[2], vert[16], vert[1], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[2], vert[1], vert[13], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[2], vert[13], vert[2], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[2], vert[2], vert[17], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[3], vert[11], vert[3], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[3], vert[3], vert[17], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[3], vert[17], vert[2], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[3], vert[2], vert[10], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[3], vert[10], vert[11], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[4], vert[15], vert[12], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[4], vert[12], vert[0], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[4], vert[0], vert[8], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[4], vert[8], vert[7], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[4], vert[7], vert[15], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[5], vert[9], vert[1], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[5], vert[1], vert[13], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[5], vert[13], vert[14], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[5], vert[14], vert[6], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[5], vert[6], vert[9], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[6], vert[10], vert[2], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[6], vert[2], vert[13], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[6], vert[13], vert[14], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[6], vert[14], vert[5], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[6], vert[5], vert[10], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[7], vert[15], vert[12], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[7], vert[12], vert[3], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[7], vert[3], vert[11], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[7], vert[11], vert[4], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[7], vert[4], vert[15], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[8], vert[15], vert[7], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[8], vert[7], vert[19], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[8], vert[19], vert[18], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[8], vert[18], vert[4], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[8], vert[4], vert[15], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[9], vert[7], vert[8], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[9], vert[8], vert[9], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[9], vert[9], vert[6], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[9], vert[6], vert[19], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[9], vert[19], vert[7], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[10], vert[18], vert[19], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[10], vert[19], vert[6], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[10], vert[6], vert[14], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[10], vert[14], vert[5], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[10], vert[5], vert[18], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);

	ele = ft_lstnew(tri_factory(peaks[11], vert[18], vert[4], encode_rgb(255, 0, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[11], vert[4], vert[11], encode_rgb(255, 255, 0)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[11], vert[11], vert[10], encode_rgb(255, 0, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[11], vert[10], vert[5], encode_rgb(255, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
	ele = ft_lstnew(tri_factory(peaks[11], vert[5], vert[18], encode_rgb(0, 255, 255)));
	ft_lstadd_back(&(data->objects), ele);
}