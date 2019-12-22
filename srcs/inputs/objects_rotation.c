/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:41:41 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/22 14:48:16 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"

void change_obj_normal_x(void *obj, short id, double val)
{
	if (id == e_plane)
	{
		((t_plane *)obj)->orient.x += val;
		recalc_pl_norm(obj);
	}
	if (id == e_sq)
	{
		((t_square *)obj)->orient.x += val;
		recalc_sq_vect(obj);
	}
	if (id == e_disk)
	{
		((t_disk *)obj)->orient.x += val;
		recalc_dk_norm(obj);
	}
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

void change_obj_normal_y(void *obj, short id, double val)
{
	if (id == e_plane)
	{
		((t_plane *)obj)->orient.y += val;
		recalc_pl_norm(obj);
	}
	if (id == e_sq)
	{
		((t_square *)obj)->orient.y += val;
		recalc_sq_vect(obj);
	}
	if (id == e_disk)
	{
		((t_disk *)obj)->orient.y += val;
		recalc_dk_norm(obj);
	}
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

void change_obj_normal_z(void *obj, short id, double val)
{
	if (id == e_plane)
	{
		((t_plane *)obj)->orient.z += val;
		recalc_pl_norm(obj);
	}
	if (id == e_sq)
	{
		((t_square *)obj)->orient.z += val;
		recalc_sq_vect(obj);
	}
	if (id == e_disk)
	{
		((t_disk *)obj)->orient.z += val;
		recalc_dk_norm(obj);
	}
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

int handle_object_rotation(t_data *data, int key)
{
	short type;

	type = data->cur_obj->obj_type;
	if (type == e_sphere || type == e_tri)
		return (0);
	if (key == KEY_U)
		change_obj_normal_y(data->cur_obj->obj, data->cur_obj->obj_type, 0.05);
	else if (key == KEY_O)
		change_obj_normal_y(data->cur_obj->obj, data->cur_obj->obj_type, -0.05);
	else if (key == KEY_L)
		change_obj_normal_z(data->cur_obj->obj, data->cur_obj->obj_type, 0.05);
	else if (key == KEY_J)
		change_obj_normal_z(data->cur_obj->obj, data->cur_obj->obj_type, -0.05);
	else if (key == KEY_I)
		change_obj_normal_x(data->cur_obj->obj, data->cur_obj->obj_type, 0.05);
	else if (key == KEY_K)
		change_obj_normal_x(data->cur_obj->obj, data->cur_obj->obj_type, -0.05);
	else
		return (0);
	ft_putstr("Object rotated!\n");
	multithread_render(data);
	return (1);
}