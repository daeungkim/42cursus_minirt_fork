/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:26:20 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 13:40:40 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "key.h"

int	proper_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_ESC)
		proper_exit(data);
	else if (key == KEY_SPACE)
	{
		data->render_mode = data->render_mode ? 0 : 1;
		ft_putstr(data->render_mode ? "Render on\n" : "Render off\n");
		multithread_render(data);
	}
	else if (data->obj_selected && handle_object_movement(data, key))
		;
	else if (data->obj_selected && handle_object_rotation(data, key))
		;
	else if (key == KEY_N || key == KEY_B)
		change_camera(data, key);
	else if (handle_camera_movement(data, key))
		;
	else if (handle_camera_rotation(data, key))
		;
	return (0);
}

int	handle_click(int button, int x, int y, t_data *data)
{
	if (button == LFT_MOUSE)
	{
		multithread_render(data);
		data->t = -1;
		data->ray = compute_ray(data, data->current_cam, x, y);
		if ((data->cur_obj = find_closest_hit(data, data->ray, &(data->t))))
		{
			data->obj_selected = 1;
			mlx_string_put(data->mlx_ptr, data->mlx_win, 50, 50,
				encode_rgb(255, 0, 0), "Object selected!");
		}
		else
			data->obj_selected = 0;
	}
	else if (button == RGT_MOUSE)
	{
		multithread_render(data);
		mlx_string_put(data->mlx_ptr, data->mlx_win, 50, 50,
				encode_rgb(255, 0, 0), "Object deselected!");
		data->obj_selected = 0;
	}
	return (0);
}
