/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 19:22:00 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include "key.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void	set_data(t_data *data)
{
	data->save = 0;
	data->res.loaded = 0;
	data->amb.loaded = 0;
	data->cameras = 0;
	data->objects = 0;
	data->lights = 0;
	data->no_render_amb = encode_rgb(200, 200, 200);
	data->bckgd_colour = encode_rgb(50, 50, 50);
	data->render_mode = 1;
	data->cam_num = 0;
	data->obj_selected = 0;
	data->max_ref = 0;
}

int		exe_rt(t_data *d, char *file)
{
	if (!load_data(d, file))
		return (0);
	d->mlx_ptr = mlx_init();
	if (!(d->mlx_img = mlx_new_image(d->mlx_ptr, d->res.x, d->res.y)))
		return (0);
	d->data_add = (int *)mlx_get_data_addr(d->mlx_img, &(d->pixsize),
					&(d->pixsizeline), &(d->endian));
	d->mlx_win = mlx_new_window(d->mlx_ptr, d->res.x, d->res.y, "Dat_window");
	d->current_cam = d->cameras->content;
	d->max_cam = ft_lstsize(d->cameras);
	multithread_render(d);
	return (1);
}

int		main(int ac, char **av)
{
	t_data	data;

	set_data(&data);
	if (ac == 3)
		if (!ft_strcmp(av[2], "-save"))
			data.save = 1;
	if (ac == 1 || ac > 3)
		return (0);
	time(NULL);
	if (!exe_rt(&data, av[1]))
		return (0);
	if (data.save)
		return (save_image(&data));
	mlx_hook(data.mlx_win, 2, (1L << 0), key_release, &data);
	mlx_hook(data.mlx_win, 17, (1L << 17), proper_exit, &data);
	mlx_hook(data.mlx_win, 5, (1L << 0), handle_click, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.mlx_win);
	return (0);
}
