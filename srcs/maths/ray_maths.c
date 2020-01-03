/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:12:36 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/03 15:41:46 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void  check_first_hit(t_geo **hit_obj, t_rt_param p,
                            double *hit, t_list *first)
{
    if (p.v && (((p.i > 0 && *hit < 0) || (p.i > 0 && p.i < *hit))))
    {
        *hit = p.i;
        *hit_obj = first->content;
    }
    else if (((t_geo *)(first->content))->obj_type == e_cyl && 
		p.v_2 && ((p.i_2 > 0 && *hit < 0) || (p.i_2 > 0 && p.i_2 < *hit)))
    {
        *hit = p.i_2;
        *hit_obj = first->content;
    }
}

/*
** We will rotate around each axis depending on orientation vector given
*/
t_vector3   compute_ray(const t_data *data, t_camera *cam,
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

t_geo       *find_closest_hit(t_data *data, t_vector3 ray, double *hit)
{
	t_geo	*hit_obj;
	t_list	*first;
	t_rt_param p;
	
	hit_obj = 0;
	first = data->objects;
	while (first)
	{
		p = set_param(data->current_cam->pos, ray, -1, 0);
		if (raytrace(first->content, &p))
            check_first_hit(&hit_obj, p, hit, first);
		first = first->next;
	}
	return (hit_obj);
}