/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:43:43 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/03 15:44:18 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector3 angle_cases(t_data data, t_geo *rt_obj, t_vector3 inter_point,
					t_light *light)
{
	t_rt_param	param1;
	t_rt_param	param2;
	t_vector3	norm_vect;

	norm_vect = normalise_vector(get_normal_vector(inter_point, rt_obj));
	if (rt_obj->obj_type == e_plane || rt_obj->obj_type == e_sq ||
		rt_obj->obj_type == e_disk || rt_obj->obj_type == e_tri)
	{
		if (distance(light->pos, point_from_ray(inter_point, norm_vect, 1)) >
			distance(light->pos, inter_point))
			return (scalar_vect(norm_vect, -1.0));
		param1 = set_param(light->pos, norm_vect, 0, rt_obj->obj);
		param2 = set_param(point_from_ray(inter_point, data.ray, -data.t / 2),
							norm_vect, -1, rt_obj->obj);
		rt_obj->find_inter(&param1);
		rt_obj->find_inter(&param2);
		if ((param1.i < 0 && param2.i > 0) || (param1.i > 0 && param2.i < 0))
			return (scalar_vect(norm_vect, -1.0));
	}
	return (norm_vect);
}

/*
** Will need a lot of refactoring
*/
double get_light_angle(t_data data, t_light *light, double t, t_geo *rt_obj)
{
	t_vector3	inter_point;
	t_vector3	norm_vect;
	t_camera	*cam;
	t_rt_param	param1;

	cam = data.current_cam;
	inter_point = point_from_ray(cam->pos, data.ray, t);
	norm_vect = angle_cases(data, rt_obj, inter_point, light);
	if (rt_obj->obj_type == e_cyl)
	{
		param1 = set_param(data.current_cam->pos, data.ray, 0, rt_obj->obj);
		if (raytrace(rt_obj, &param1))
			if (!param1.v && param1.v_2 && param1.i_2 > 0)
				norm_vect = scalar_vect(norm_vect, -1.0);
	}
	return (angle_between_vectors(norm_vect,
								direction_vector(inter_point, light->pos)));
}

/*
** Shit's too long. REFACTOR YOU NOOB
*/
int is_light_obstructed(t_data data, t_geo *rt_obj, t_light *light)
{	
	t_vector3	start;
	t_vector3	light_ray;
	t_list		*ele;
	t_rt_param	param;
	t_rt_param	param2;

	start = point_from_ray(data.current_cam->pos, data.ray, data.t);
	light_ray = normalise_vector(direction_vector(start, light->pos));
	ele = data.objects;
	while (ele)
	{
		if (ele->content != rt_obj)
		{
			param = set_param(start, light_ray, -1, 0);
			if (((t_geo *)ele->content)->obj_type == e_cyl || ((t_geo *)ele->content)->obj_type == e_cone)
			{
				if (raytrace(ele->content, &param))
					if (distance(start, light->pos) >
					distance(light->pos, point_from_ray(start, light_ray, param.v_2 ? param.i_2 : param.i)))
						return (1);
			}
			else if (raytrace(ele->content, &param))
			{
				if (distance(start, light->pos) > 
				distance(light->pos, point_from_ray(start, light_ray, param.i > 0 ? param.i : param.i_2)) &&
				distance(start, light->pos) > distance (start, point_from_ray(start, light_ray, param.i > 0 ? param.i : param.i_2)))
					return (1);
			}
		}
		else if (rt_obj->obj_type == e_cyl)
		{
			param = set_param(point_from_ray(start, light_ray, 0.0001), light_ray, -1, 0);
			if (raytrace(ele->content, &param))
				if (param.v_2 && param.i_2 > 0 && distance(start, light->pos) >
					distance(light->pos,
					point_from_ray(start, light_ray, param.i_2)) &&
					distance(start, light->pos) > distance(start,
					point_from_ray(start, light_ray, param.i_2)))
						return (1);
		}
		else if (rt_obj->obj_type == e_torus)
		{
			param = set_param(point_from_ray(start, light_ray, 0.0001), light_ray, -1, 0);
			if (raytrace(ele->content, &param))
				if (param.v_2 && param.i_2 > 0 && distance(start, light->pos) >
					distance(light->pos,
					point_from_ray(start, light_ray, param.i_2)) &&
					distance(start, light->pos) > distance(start,
					point_from_ray(start, light_ray, param.i_2)))
						return (1);
		}
		else if (rt_obj->obj_type == e_sq || rt_obj->obj_type == e_plane || rt_obj->obj_type == e_tri)
		{
			param = set_param(light->pos, get_normal_vector(start, rt_obj), -1, rt_obj->obj);
			param2 = set_param(data.current_cam->pos, get_normal_vector(start, rt_obj), -1, rt_obj->obj);
			rt_obj->find_inter(&param);
			rt_obj->find_inter(&param2);
			if ((param.i < 0 && param2.i > 0) || (param.i > 0 && param2.i < 0))
				return (1);
		}
		ele = ele->next;
	}
	return (0);
}

int calc_colour_from_light(t_data data, t_geo *rt_obj)
{
	t_list *first;
	t_light *light;
	double ang;
	int final_light;
	int l_val;

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