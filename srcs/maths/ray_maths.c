/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:36 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 19:23:02 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	check_first_hit(t_geo **hit_obj, t_rt_param p,
			double *hit, t_list *first)
{
	if (p.v && p.i > 0 && (*hit < 0 || p.i < *hit))
	{
		*hit = p.i;
		*hit_obj = first->content;
	}
	if (p.v_2 && p.i_2 > 0 && (*hit < 0 || p.i_2 < *hit))
	{
		*hit = p.i_2;
		*hit_obj = first->content;
	}
	if (p.v_3 && p.i_3 > 0 && (*hit < 0 || p.i_3 < *hit))
	{
		*hit = p.i_3;
		*hit_obj = first->content;
	}
	if (p.v_4 && p.i_4 > 0 && (*hit < 0 || p.i_4 < *hit))
	{
		*hit = p.i_4;
		*hit_obj = first->content;
	}
}

t_rt_param	set_param(t_vector3 o, t_vector3 r, double i, void *ob)
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

/*
** We will rotate around each axis depending on orientation vector given
*/

t_vector3	compute_ray(const t_data *data, t_camera *cam,
						const double x, const double y)
{
	double		sc_height;
	double		sc_width;
	double		pix_shift;
	t_vector3	base_dir;
	t_vector3	ray;

	base_dir = scalar_vect(cam->vector_x, (double)SCREEN_L);
	sc_width = (double)SCREEN_L * tan(to_rad(cam->fov / 2)) * 2;
	sc_height = sc_width * (data->res.y / data->res.x);
	pix_shift = sc_width / ((double)data->res.x - 1);
	ray = add_vect(base_dir, scalar_vect(cam->vector_z,
							((2 * (x + 0.5) - data->res.x) / 2) * pix_shift));
	ray = add_vect(ray, scalar_vect(cam->vector_y,
							((-2 * (y + 0.5) + data->res.y) / 2) * pix_shift));
	ray = normalise_vector(ray);
	return (ray);
}

t_geo		*find_closest_hit(t_data *d)
{
	t_geo		*hit_obj;
	t_list		*first;
	t_rt_param	p;
	t_vector3	norm;

	hit_obj = 0;
	first = d->objects;
	while (first)
	{
		p = set_param(d->ray_origin, d->ray, -1, 0);
		if (raytrace(first->content, &p))
			check_first_hit(&hit_obj, p, &(d->t), first);
		first = first->next;
	}
	if (hit_obj && hit_obj->ref && d->t > 0 && d->ref_lvl < d->max_ref)
	{
		d->ref_lvl++;
		d->ray_origin = point_from_ray(d->ray_origin, d->ray, d->t);
		norm = get_normal_vector(d->ray_origin, hit_obj, d);
		d->ray_origin = add_vect(d->ray_origin, scalar_vect(norm, 0.001));
		d->ray = reflect_vector(d->ray, norm);
		d->t = -1.0;
		return (find_closest_hit(d));
	}
	return (hit_obj);
}

t_geo		*find_closest_hit_non_ref(t_data *data)
{
	t_geo		*hit_obj;
	t_list		*first;
	t_rt_param	p;

	hit_obj = 0;
	first = data->objects;
	while (first)
	{
		p = set_param(data->current_cam->pos, data->ray, -1, 0);
		if (raytrace(first->content, &p))
			check_first_hit(&hit_obj, p, &(data->t), first);
		first = first->next;
	}
	return (hit_obj);
}
