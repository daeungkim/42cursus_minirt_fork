/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_factories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:04:15 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/18 18:05:41 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_geo *sphere_factory(t_vector3 centre, double diametre, int colour)
{
	t_sphere	*sp;
	t_geo		*sp_obj;

	if (!(sp = malloc(sizeof(t_sphere))))
		return (NULL);
	if (!(sp_obj = malloc(sizeof(t_geo))))
		return (NULL);
	sp->centre.x = centre.x;
	sp->centre.y = centre.y;
	sp->centre.z = centre.z;
	sp->diametre = diametre;
	sp_obj->colour = colour;
	sp_obj->obj = sp;
	sp_obj->find_inter = &raytrace_sphere;
	sp_obj->get_normal_vector = &normal_vector_sphere;
	sp_obj->obj_type = e_sphere;
	return (sp_obj);
}

t_geo *plane_factory(t_vector3 centre, t_vector3 orient, int colour)
{
	t_plane *plane;
	t_geo	*plane_obj;

	if (!(plane = malloc(sizeof(t_plane))))
		return (NULL);
	if (!(plane_obj = malloc(sizeof(t_geo))))
		return (NULL);
	plane_obj->colour = colour;
	plane->centre.x = centre.x;
	plane->centre.y = centre.y;
	plane->centre.z = centre.z;
	plane->normal = apply_orientation(create_vector(0, 1, 0), orient);
	plane_obj->obj = plane;
	plane_obj->find_inter = &raytrace_plane;
	plane_obj->get_normal_vector = &normal_vector_plane;
	plane_obj->obj_type = e_plane;
	return (plane_obj);
}

t_geo *square_factory(t_vector3 centre, t_vector3 orient, double height, int colour)
{
	t_square *square;
	t_geo	*square_obj;

	if (!(square = malloc(sizeof(t_square))))
		return (NULL);
	if (!(square_obj = malloc(sizeof(t_geo))))
		return (NULL);
	square_obj->colour = colour;
	square->centre = centre;
	square->orient = orient;
	square->normal = apply_orientation(create_vector(0, 1, 0), orient);
	square->x = apply_orientation(create_vector(1, 0, 0), orient);
	square->x = scalar_vect(square->x, height);
	square->z = apply_orientation(create_vector(0, 0, 1), orient);
	square->z = scalar_vect(square->z, height);
	square->height = height;
	square_obj->obj = square;
	square_obj->find_inter = &raytrace_square;
	square_obj->get_normal_vector = &normal_vector_square;
	square_obj->obj_type = e_sq;
	return (square_obj);
}

t_geo *tri_factory(t_vector3 p1, t_vector3 p2, t_vector3 p3, int colour)
{
	t_triangle *triangle;
	t_geo	*tri_obj;

	if (!(triangle = malloc(sizeof(t_square))))
		return (NULL);
	if (!(tri_obj = malloc(sizeof(t_geo))))
		return (NULL);
	tri_obj->colour = colour;
	triangle->p1 = p1;
	triangle->p2 = p2;
	triangle->p3 = p3;
	triangle->normal = define_tri_plane(p1, p2, p3);
	tri_obj->obj = triangle;
	tri_obj->find_inter = &raytrace_triangle;
	tri_obj->get_normal_vector = &normal_vector_triangle;
	tri_obj->obj_type = e_tri;
	return (tri_obj);
}

t_geo *disk_factory(t_vector3 centre, t_vector3 orient, double diametre, int colour)
{
	t_disk *disk;
	t_geo	*disk_obj;

	if (!(disk = malloc(sizeof(t_disk))))
		return (NULL);
	if (!(disk_obj = malloc(sizeof(t_geo))))
		return (NULL);
	disk_obj->colour = colour;
	disk->centre = centre;
	disk->orient = orient;
	disk->normal = apply_orientation(create_vector(0, 1, 0), orient);
	disk->diametre = diametre;
	disk_obj->obj = disk;
	disk_obj->find_inter = &raytrace_disk;
	disk_obj->get_normal_vector = &normal_vector_disk;
	disk_obj->obj_type = e_disk;
	return (disk_obj);
}