/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_normal_calc_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:41:54 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:52:23 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"

void	recalc_torus_norm(t_orus *to)
{
	to->normal = apply_orientation(create_vector(0, 1, 0), to->orient);
}

void	change_obj_normal_x_2(void *obj, short id, double val)
{
	if (id == e_cyl)
	{
		((t_cylindre *)obj)->real_ori.x += val;
		recalc_cy_norm(obj);
	}
	if (id == e_cone)
	{
		((t_cone *)obj)->orient.x += val;
		recalc_cone_norm(obj);
	}
	if (id == e_torus)
	{
		((t_orus *)obj)->orient.x += val;
		recalc_torus_norm(obj);
	}
}

void	change_obj_normal_y_2(void *obj, short id, double val)
{
	if (id == e_cyl)
	{
		((t_cylindre *)obj)->real_ori.y += val;
		recalc_cy_norm(obj);
	}
	if (id == e_cone)
	{
		((t_cone *)obj)->orient.y += val;
		recalc_cone_norm(obj);
	}
	if (id == e_torus)
	{
		((t_orus *)obj)->orient.y += val;
		recalc_torus_norm(obj);
	}
}

void	change_obj_normal_z_2(void *obj, short id, double val)
{
	if (id == e_cyl)
	{
		((t_cylindre *)obj)->real_ori.z += val;
		recalc_cy_norm(obj);
	}
	if (id == e_cone)
	{
		((t_cone *)obj)->orient.z += val;
		recalc_cone_norm(obj);
	}
	if (id == e_torus)
	{
		((t_orus *)obj)->orient.z += val;
		recalc_torus_norm(obj);
	}
}
