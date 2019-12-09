/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:24:19 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/09 22:59:50 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"
#include <stdio.h>

void apply_rotation(t_camera *cam)
{
	//t_vector3 temp;
	// cam->vector_x = apply_orientation(create_vector(1, 0, 0), cam->orient);
	// cam->vector_y = apply_orientation(create_vector(0, 1, 0), cam->orient);
	// cam->vector_z = apply_orientation(create_vector(0, 0, 1), cam->orient);
	// cam->vector_x = apply_orientation(cam->vector_x, cam->orient);
	// cam->vector_y = apply_orientation(cam->vector_y, cam->orient);
	// cam->vector_z = apply_orientation(cam->vector_z, cam->orient);
	if (cam->orient.x != 0)
	{
		cam->vector_y = apply_orientation(cam->vector_y, cam->orient);
		cam->vector_z = apply_orientation(cam->vector_z, cam->orient);
		//cam->vector_y = temp;
	}
	else if (cam->orient.y != 0)
	{
		cam->vector_x = apply_orientation(cam->vector_x, cam->orient);
		cam->vector_z = apply_orientation(cam->vector_z, cam->orient);
		//cam->vector_x = temp;
	}
	else if (cam->orient.z != 0)
	{
		cam->vector_x = apply_orientation(cam->vector_x, cam->orient);
		cam->vector_y = apply_orientation(cam->vector_y, cam->orient);
		//cam->vector_x = temp;
	}
}

t_camera *get_cam(t_data *data, int index)
{
	t_list *cam;

	cam = data->cameras;
	while (index)
	{
		index--;
		cam = cam->next;
	}
	return (cam->content);
}

int change_camera(t_data *data, int key)
{
	if (data->max_cam <= 1)
		return (0);
	if (key == KEY_N)
		data->cam_num++;
	else if (key == KEY_B)
		data->cam_num--;
	if (data->cam_num == data->max_cam)
		data->cam_num = 0;
	if (data->cam_num < 0)
		data->cam_num = data->max_cam - 1;
	data->current_cam = get_cam(data, data->cam_num);
	ft_putstr("camera changed\n");
	multithread_render(data);
	return (0);
}

int handle_camera_movement(t_data *data, int key)
{
	t_vector3 pos;
	t_camera *cam;

	cam = data->current_cam;
	pos = data->current_cam->pos;
	if (data->render_mode)
		return (0);
    if (key == KEY_Q)
		data->current_cam->pos = point_from_ray(pos, cam->vector_y, 0.3);
    else if (key == KEY_E)
		data->current_cam->pos = point_from_ray(pos, cam->vector_y, -0.3);
    else if (key == KEY_D)
		data->current_cam->pos = point_from_ray(pos, cam->vector_z, 0.3);
	else if (key == KEY_A)
		data->current_cam->pos = point_from_ray(pos, cam->vector_z, -0.3);
    else if (key == KEY_W)
		data->current_cam->pos = point_from_ray(pos, cam->vector_x, 0.3);
	else if (key == KEY_S)
		data->current_cam->pos = point_from_ray(pos, cam->vector_x, -0.3);
	else
		return (0);
	ft_putstr("camera moved\n");
	multithread_render(data);
	return (1);
}

int handle_camera_rotation(t_data *data, int key)
{
	data->current_cam->orient.x = 0;
	data->current_cam->orient.y = 0;
	data->current_cam->orient.z = 0;
	// printf("vector x = |%g|%g|%g|\n", data->current_cam->vector_x.x, data->current_cam->vector_x.y, data->current_cam->vector_x.z);
	// printf("vector y = |%g|%g|%g|\n", data->current_cam->vector_y.x, data->current_cam->vector_y.y, data->current_cam->vector_y.z);
	// printf("vector z = |%g|%g|%g|\n", data->current_cam->vector_z.x, data->current_cam->vector_z.y, data->current_cam->vector_z.z);

	if (data->render_mode)
		return (0);
    if (key == KEY_U)
		data->current_cam->orient.x += 0.05;
    else if (key == KEY_O)
		data->current_cam->orient.x -= 0.05;
    else if (key == KEY_I)
		data->current_cam->orient.z += 0.05;
	else if (key == KEY_K)
		data->current_cam->orient.z -= 0.05;
    else if (key == KEY_J)
		data->current_cam->orient.y += 0.05;
	else if (key == KEY_L)
		data->current_cam->orient.y -= 0.05;
	else
		return (0);
	apply_rotation(data->current_cam);
	// printf("\nvector x = |%g|%g|%g|\n", data->current_cam->vector_x.x, data->current_cam->vector_x.y, data->current_cam->vector_x.z);
	// printf("vector y = |%g|%g|%g|\n", data->current_cam->vector_y.x, data->current_cam->vector_y.y, data->current_cam->vector_y.z);
	// printf("vector z = |%g|%g|%g|\n", data->current_cam->vector_z.x, data->current_cam->vector_z.y, data->current_cam->vector_z.z);
	printf("Angle XY = %g\n", angle_between_vectors(data->current_cam->vector_x, data->current_cam->vector_y) * 180 / M_PI);
	printf("Angle YZ = %g\n", angle_between_vectors(data->current_cam->vector_y, data->current_cam->vector_z) * 180 / M_PI);
	printf("Angle ZX = %g\n", angle_between_vectors(data->current_cam->vector_z, data->current_cam->vector_x) * 180 / M_PI);

	
	ft_putstr("Camera rotated\n");
	multithread_render(data);
	return (1);
}