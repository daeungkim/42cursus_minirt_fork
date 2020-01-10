/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:43:43 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/10 10:31:36 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double		get_light_angle(t_data data, t_light *light, double t,
			t_geo *rt_obj)
{
	t_vector3	inter_point;
	t_vector3	norm_vect;
	t_camera	*cam;

	cam = data.current_cam;
	inter_point = point_from_ray(cam->pos, data.ray, t);
	norm_vect = get_normal_vector(inter_point, rt_obj, &data);
	return (angle_between_vectors(norm_vect,
								direction_vector(inter_point, light->pos)));
}

double		get_valid_t(t_rt_param param)
{
	double valid;

	valid = -1.0;
	if (param.i > 0 && param.v && (valid < 0 || param.i < valid))
		valid = param.i;
	if (param.i_2 > 0 && param.v_2 && (valid < 0 || param.i_2 < valid))
		valid = param.i_2;
	if (param.i_3 > 0 && param.v_3 && (valid < 0 || param.i_3 < valid))
		valid = param.i_3;
	if (param.i_4 > 0 && param.v_4 && (valid < 0 || param.i_4 < valid))
		valid = param.i_4;
	return (valid);
}

int			is_light_obstructed(t_data data, t_geo *rt_obj, t_light *light)
{
	t_vector3	start;
	t_vector3	light_ray;
	t_list		*ele;
	t_rt_param	param;
	double		valid_t;

	start = point_from_ray(data.current_cam->pos, data.ray, data.t);
	light_ray = normalise_vector(direction_vector(start, light->pos));
	start = add_vect(start,
			scalar_vect(get_normal_vector(start, rt_obj, &data), 0.01));
	ele = data.objects;
	while (ele)
	{
		param = set_param(start, light_ray, -1, 0);
		if (raytrace(ele->content, &param))
		{
			valid_t = get_valid_t(param);
			if (valid_t > 0)
				if (distance(start, light->pos) >
					distance(start, point_from_ray(start, light_ray, valid_t)))
					return (1);
		}
		ele = ele->next;
	}
	return (0);
}

int			calc_colour_from_light(t_data data, t_geo *rt_obj)
{
	t_list	*first;
	t_light	*light;
	double	ang;
	int		final_light;
	int		l_val;

	final_light = 0;
	first = data.lights;
	while (first && data.render_mode)
	{
		light = first->content;
		if (!is_light_obstructed(data, rt_obj, light))
		{
			ang = get_light_angle(data, light, data.t, rt_obj);
			if (ang < M_PI_2 && ang > -M_PI_2)
			{
				l_val = apply_intensity_rgb(light->colour, sin(M_PI_2 - ang));
				final_light = add_lights(final_light, l_val);
			}
		}
		first = first->next;
	}
	final_light = add_lights(final_light,
					!data.render_mode ? data.no_render_amb : data.amb.colour);
	return (filter_colours_rgb(final_light, rt_obj->colour));
}
