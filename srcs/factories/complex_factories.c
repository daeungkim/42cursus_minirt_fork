/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_factories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:07:36 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/22 14:45:57 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_geo *cyl_factory(t_vector3 centre, t_vector3 orient, t_vector3 dia_height, int colour)
{
	t_cylindre	*cyl;
	t_geo		*cyl_obj;

	if (!(cyl = malloc(sizeof(t_cylindre))))
		return (NULL);
	if (!(cyl_obj = malloc(sizeof(t_geo))))
		return (NULL);
	cyl_obj->colour = colour;
	cyl->centre = centre;
	cyl->real_ori = orient;
	cyl->orient = apply_orientation(create_vector(0, 1, 0), orient);
	cyl->diametre = dia_height.x;
	cyl->height = dia_height.y;
	cyl_obj->obj = cyl;
	cyl_obj->find_inter = &raytrace_cyl;
	cyl_obj->get_normal_vector = &normal_vector_cyl;
	cyl_obj->obj_type = e_cyl;
	return (cyl_obj);
}

t_geo *cone_factory(t_vector3 centre, t_vector3 orient, t_vector3 dia_height, int colour)
{
	t_cone	*cone;
	t_geo	*cone_obj;

	if (!(cone = malloc(sizeof(t_cone))))
		return (NULL);
	if (!(cone_obj = malloc(sizeof(t_geo))))
		return (NULL);
	cone_obj->colour = colour;
	cone->centre = centre;
	cone->orient = orient;
	cone->normal = apply_orientation(create_vector(0, 1, 0), orient);
	cone->diametre = dia_height.x;
	cone->height = dia_height.y;
	cone_obj->obj = cone;
	cone_obj->find_inter = &raytrace_cone;
	cone_obj->get_normal_vector = &normal_vector_cone;
	cone_obj->obj_type = e_cone;
	return (cone_obj);
}

t_geo *torus_factory(t_vector3 centre, t_vector3 orient, t_vector3 i_o, int colour)
{
	t_orus	*torus;
	t_geo	*torus_obj;

	if (!(torus = malloc(sizeof(t_orus))))
		return (NULL);
	if (!(torus_obj = malloc(sizeof(t_geo))))
		return (NULL);
	torus_obj->colour = colour;
	torus->centre = centre;
	torus->orient = orient;
	torus->normal = apply_orientation(create_vector(0, 1, 0), orient);
	torus->i_dia = i_o.x / 2;
	torus->o_dia = i_o.y / 2;
	torus_obj->obj = torus;
	torus_obj->find_inter = &raytrace_torus;
	torus_obj->get_normal_vector = &normal_vector_torus;
	torus_obj->obj_type = e_torus;
	return (torus_obj);
}