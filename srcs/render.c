/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 17:23:56 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 18:11:27 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int bcgrd_colour(int lvl)
{
	return (encode_rgb(50 * pow(0.94, lvl),
			50 * pow(0.975, lvl), 50 * pow(0.94, lvl)));
}

void	*compute_render_t(void *data)
{
	int			i;
	int			j;
	t_data		*d;

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
			d->ref_lvl = 0;
			d->ray = compute_ray(d, d->current_cam, j, i);
			d->ray_origin = d->current_cam->pos;
			if ((d->cur_obj = find_closest_hit(d)))
				d->workable[j] = calc_colour_from_light(*d, d->cur_obj);
			else
				d->workable[j] = bcgrd_colour(d->ref_lvl);
		}
	}
	d->cur_obj = 0;
	return (NULL);
}

void	multithread_render(t_data *data)
{
	pthread_t	th[CORES];
	t_data		dups[CORES];
	int			i;

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
