/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/03 15:44:14 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include "key.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h> 


t_rt_param set_param(t_vector3 o, t_vector3 r, double i, void *ob)
{
	t_rt_param param;

	param.origin = o;
	param.ray = r;
	param.i = i;
	param.v = 0;
	param.i_2 = -1;
	param.v_2 = 0;
	param.i_3 = -1;
	param.v_3 = 0;
	param.i_4 = -1;
	param.v_4 = 0;
	param.object = ob;
	return (param);
}


void set_data(t_data *data)
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
}

void *compute_render_t(void *data)
{
	int i;
	int j;
	t_data *d;

	d = data;
	i = d->start - 1;
	d->workable = d->data_add + (d->pixsizeline / 4) * d->start;
	while (++i < d->end)
	{
		if (i != d->start)
			d->workable += d->pixsizeline / 4;
		j = -1;
		while (++j < d->res.x)
		{
			d->t = -1;
			d->ray = compute_ray(d, d->current_cam, j, i);
			if ((d->cur_obj = find_closest_hit(d, d->ray, &(d->t))))
				d->workable[j] = calc_colour_from_light(*d, d->cur_obj);
			else
				d->workable[j] = encode_rgb(50, 50, 50);
		}
	}
	d->cur_obj = 0;
	return (NULL);
}

void multithread_render(t_data *data)
{
	pthread_t	th[CORES];
	t_data		dups[CORES];
	int i;
	
	i = -1;
	while (++i < CORES)
	{
		ft_memcpy((void *)&dups[i], (void *)data, sizeof(t_data));
		dups[i].start = data->res.y / CORES * i;
		dups[i].end = data->res.y / CORES * (i + 1);
		dups[i].end = i == CORES - 1 ? data->res.y : dups[i].end;
		pthread_create(&th[i], NULL, compute_render_t, &dups[i]);
	}
	while (i-- > 0)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
}

int proper_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int key_release(int key, t_data *data)
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

int handle_click(int button, int x, int y, t_data *data)
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

int main(int ac, char **av)
{
	t_data data;
	clock_t start, end;

	long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Processor count is %ld\n", number_of_processors);
	set_data(&data);
	if (ac == 3)
		if (!ft_strcmp(av[2], "-save"))
			data.save = 1;
	if (ac == 1 || ac > 3)
		return (0);
	time(NULL);
	start = clock();
	if (!load_data(&data, av[1]))
		return (0);
	data.mlx_ptr = mlx_init();
	if (!(data.mlx_img = mlx_new_image(data.mlx_ptr, data.res.x, data.res.y)))
		return (0);
	data.data_add= (int *)mlx_get_data_addr(data.mlx_img, &(data.pixsize), &(data.pixsizeline), &(data.endian));
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.res.x, data.res.y, "Dat_window");
	data.current_cam = data.cameras->content;
	data.max_cam = ft_lstsize(data.cameras);
	multithread_render(&data);
	if (data.save)
		return (save_image(&data));
	mlx_hook(data.mlx_win, 2, (1L << 0), key_release, &data);
	mlx_hook(data.mlx_win, 17, (1L << 17), proper_exit, &data);
	mlx_hook(data.mlx_win, 5, (1L << 0), handle_click, &data);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC / CORES;
	printf("Time taken is %f\n", cpu_time_used);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.mlx_win);
	return (0);

}

int main1()
{
    t_quartic q;
    t_rt_param p;
    q.a = -1.7;
    q.b = -1.5;
    q.c = 1.6;
    q.d = 3.8;
    q.e = -2.32;

    p = set_param(create_vector(0, 0, 0), create_vector(0, 0, 0), 0, 0);
    
	int res;
	
	printf("%d real solutions\n",res = solve_quartic(q, &p));
	if (p.v && p.v_2)
        printf("1st root = %g\n2nd root = %g\n", p.i, p.i_2);
    if (p.v_3 && p.v_4)
        printf("1st root = %g\n2nd root = %g\n", p.i_3, p.i_4);

	p = set_param(create_vector(0, 0, 0), create_vector(0, 0, 0), 0, 0);

	printf("%d real solutions for 2nd\n",res = solve_quartic1(q, &p));
	if (p.v && p.v_2)
        printf("1st root = %g\n2nd root = %g\n", p.i, p.i_2);
    if (p.v_3 && p.v_4)
        printf("1st root = %g\n2nd root = %g\n", p.i_3, p.i_4);
		return (0);
}