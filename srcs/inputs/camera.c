/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:24:19 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:40:56 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"

void		apply_rotation(t_camera *cam)
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

t_camera	*get_cam(t_data *data, int index)
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

int			change_camera(t_data *data, int key)
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

int			handle_camera_movement(t_data *data, int key)
{
	t_vector3	pos;
	t_camera	*cam;

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

int			handle_camera_rotation(t_data *data, int key)
{
	data->current_cam->orient.x = 0;
	data->current_cam->orient.y = 0;
	data->current_cam->orient.z = 0;
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
	ft_putstr("Camera rotated\n");
	multithread_render(data);
	return (1);
}
