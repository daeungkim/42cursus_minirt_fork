/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:41:41 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/11 12:59:21 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"
#include <stdio.h>

void change_centre_y(void *obj, short id, double dist)
{
	if (id == e_sphere)
		((t_sphere *)obj)->centre.y += dist;
	if (id == e_plane)
		((t_plane *)obj)->centre.y += dist;
	if (id == e_sq)
		((t_square *)obj)->centre.y += dist;
	if (id == e_disk)
		((t_disk *)obj)->centre.y += dist;
	if (id == e_cyl)
		((t_cylindre *)obj)->centre.y += dist;
	if (id == e_tri)
	{
		((t_triangle *)obj)->p1.y += dist;
		((t_triangle *)obj)->p2.y += dist;
		((t_triangle *)obj)->p3.y += dist;
	}
}

void change_centre_z(void *obj, short id, double dist)
{
	if (id == e_sphere)
		((t_sphere *)obj)->centre.z += dist;
	if (id == e_plane)
		((t_plane *)obj)->centre.z += dist;
	if (id == e_sq)
		((t_square *)obj)->centre.z += dist;
	if (id == e_disk)
		((t_disk *)obj)->centre.z += dist;
	if (id == e_cyl)
		((t_cylindre *)obj)->centre.z += dist;
	if (id == e_tri)
	{
		((t_triangle *)obj)->p1.z += dist;
		((t_triangle *)obj)->p2.z += dist;
		((t_triangle *)obj)->p3.z += dist;
	}
}

void change_centre_x(void *obj, short id, double dist)
{
	if (id == e_sphere)
		((t_sphere *)obj)->centre.x += dist;
	if (id == e_plane)
		((t_plane *)obj)->centre.x += dist;
	if (id == e_sq)
		((t_square *)obj)->centre.x += dist;
	if (id == e_disk)
		((t_disk *)obj)->centre.x += dist;
	if (id == e_cyl)
		((t_cylindre *)obj)->centre.x += dist;
	if (id == e_tri)
	{
		((t_triangle *)obj)->p1.x += dist;
		((t_triangle *)obj)->p2.x += dist;
		((t_triangle *)obj)->p3.x += dist;
	}
}

int handle_object_movement(t_data *data, int key)
{
	t_vector3 pos;

	pos = data->current_cam->pos;
	if (data->render_mode)
		return (0);
	if (key == KEY_Q)
		change_centre_y(data->cur_obj->obj, data->cur_obj->obj_type, 0.3);
	else if (key == KEY_E)
		change_centre_y(data->cur_obj->obj, data->cur_obj->obj_type, -0.3);
	else if (key == KEY_D)
		change_centre_z(data->cur_obj->obj, data->cur_obj->obj_type, 0.3);
	else if (key == KEY_A)
		change_centre_z(data->cur_obj->obj, data->cur_obj->obj_type, -0.3);
	else if (key == KEY_W)
		change_centre_x(data->cur_obj->obj, data->cur_obj->obj_type, 0.3);
	else if (key == KEY_S)
		change_centre_x(data->cur_obj->obj, data->cur_obj->obj_type, -0.3);
	else
		return (0);
	ft_putstr("Object moved\n");
	multithread_render(data);
	return (1);
}

void apply_rotation1(t_camera *cam)
{
	if (cam->orient.x != 0)
	{
		cam->vector_y = rot_axis(cam->vector_x, cam->vector_y, cam->orient.x);
		cam->vector_z = rot_axis(cam->vector_x, cam->vector_z, cam->orient.x);
	}
	else if (cam->orient.y != 0)
	{
		cam->vector_x = rot_axis(cam->vector_y, cam->vector_x, cam->orient.y);
		cam->vector_z = rot_axis(cam->vector_y, cam->vector_z, cam->orient.y);
	}
	else if (cam->orient.z != 0)
	{
		cam->vector_x = rot_axis(cam->vector_z, cam->vector_x, cam->orient.z);
		cam->vector_y = rot_axis(cam->vector_z, cam->vector_y, cam->orient.z);
	}
}

void recalc_sq_vect(t_square *sq)
{
	sq->normal = apply_orientation(create_vector(0, 1, 0), sq->orient);
	sq->x = apply_orientation(create_vector(1, 0, 0), sq->orient);
	sq->x = scalar_vect(sq->x, sq->height);
	sq->z = apply_orientation(create_vector(0, 0, 1), sq->orient);
	sq->z = scalar_vect(sq->z, sq->height);
}

void recalc_dk_norm(t_disk *dk)
{
	dk->normal = apply_orientation(create_vector(0, 1, 0), dk->orient);
}

void recalc_pl_norm(t_plane *pl)
{
	pl->normal = apply_orientation(create_vector(0, 1, 0), pl->orient);
}

void recalc_cy_norm(t_cylindre *cy)
{
	cy->orient = apply_orientation(create_vector(0, 1, 0), cy->real_ori);
}

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