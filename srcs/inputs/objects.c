/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 15:41:41 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/10 15:59:28 by cjaimes          ###   ########.fr       */
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