/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/07 00:24:56 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
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
	param.object = ob;
	return (param);
}

/*
** Apply rotation along x, y and z axis of base vector
** orientation values range from [-1.0;1.0]
** base vector is (1.0, 0.0, 0.0)
*/
t_vector3 apply_orientation(t_vector3 base, t_vector3 orient)
{
	t_vector3	ret;
	double		temp;
	double		angle;

	angle = orient.x * M_PI;
	ret.x = base.x;
	ret.y = base.y * cos(angle) - base.z * sin(angle);
	ret.z = base.y * sin(angle) + base.z * cos(angle);
	angle = orient.y * M_PI;
	temp = ret.x * cos(angle) + ret.z * sin(angle);
	ret.z = -ret.x * sin(angle) + ret.z * cos(angle);
	ret.x = temp;
	angle = orient.z * M_PI;
	temp = ret.x * cos(angle) - ret.y * sin(angle);
	ret.y = ret.x * sin(angle) + ret.y * cos(angle);
	ret.x = temp;
	return (ret);
}


/*
** We will rotate around each axis depending on orientation vector given
*/
t_vector3 compute_ray(const t_data *data, t_camera *cam, const double x, const double y)
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

int	raytrace(t_geo *geo, t_rt_param *param)
{
	param->object = geo->obj;
	if (geo->find_inter(param))
		return (1);
	return (0);
}

t_vector3 get_normal_vector(t_vector3 point, t_geo *geo)
{
	return (geo->get_normal_vector(point, geo->obj));
}

t_geo *find_closest_intersection(t_data *data, t_vector3 ray, double *inter)
{
	t_geo	*inter_obj;
	t_list	*first;
	t_rt_param param;
	
	inter_obj = 0;
	first = data->objects;
	while (first)
	{
		param = set_param(data->current_cam->pos, ray, -1, 0);
		if (raytrace(first->content, &param))
		{
			if (param.v && (((param.i > 0 && *inter < 0) ||
				(param.i > 0 && param.i < *inter))))
			{
				*inter = param.i;
				inter_obj = first->content;
			}
			else if (((t_geo *)(first->content))->obj_type == e_cyl && 
					param.v_2 && ((param.i_2 > 0 && *inter < 0) ||
					(param.i_2 > 0 && param.i_2 < *inter)))
			{
				*inter = param.i_2;
				inter_obj = first->content;
			}
		}
		first = first->next;
	}
	return (inter_obj);
}

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
	t_list		*first;
	t_rt_param	param;

	start = point_from_ray(data.current_cam->pos, data.ray, data.t);
	light_ray = normalise_vector(direction_vector(start, light->pos));
	first = data.objects;
	while (first)
	{
		if (first->content != rt_obj)
		{
			param = set_param(start, light_ray, -1, 0);
			if (((t_geo *)first->content)->obj_type == e_cyl)
			{
				if (raytrace(first->content, &param))
					if (distance(start, light->pos) >
					distance(light->pos, point_from_ray(start, light_ray, param.v_2 ? param.i_2 : param.i)))
						return (1);
			}
			else if (raytrace(first->content, &param))
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
			if (raytrace(first->content, &param))
				if (param.v_2 && param.i_2 > 0 && distance(start, light->pos) >
					distance(light->pos,
					point_from_ray(start, light_ray, param.i_2)) &&
					distance(start, light->pos) > distance(start,
					point_from_ray(start, light_ray, param.i_2)))
						return (1);
		}
		first = first->next;
	}
	return (0);
}

int calc_colour_from_light(t_data data, t_geo *rt_obj)
{
	t_list *first;
	t_light *light;
	double angle;
	int final_light;
	int current_light;

	final_light = 0;
	first = data.lights;
	while (first)
	{
		light = first->content;
		if (!is_light_obstructed(data, rt_obj, light))
		{
			angle = get_light_angle(data, light, data.t, rt_obj);
			if (angle < M_PI_2 && angle > -M_PI_2)
			{
				current_light = apply_intensity_rgb(light->colour, sin(M_PI_2 - angle));
				final_light = add_lights(final_light, current_light);
			}
		}
		first = first->next;
	}
	final_light = add_lights(final_light, data.amb.colour);
	return (filter_colours_rgb(final_light, rt_obj->colour));
}

void set_data(t_data *data)
{
	data->res.loaded = 0;
	data->amb.loaded = 0;
	data->cameras = 0;
	data->objects = 0;
	data->lights = 0;
}

int main(int ac, char **av)
{

	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int *data_adr;
	t_data data;

	clock_t start, end;
	time_t s;
	if (ac != 2)
		return (0);
	s = time(NULL);
	 start = clock();
	set_data(&data);
	if (!load_data(&data, av[1]))
		return (0);
	mlx_ptr = mlx_init();
	if (!(img_ptr = mlx_new_image(mlx_ptr, data.res.x, data.res.y)))
		return (0);
	data_adr = (int *)mlx_get_data_addr(img_ptr, &(data.pixsize), &(data.pixsizeline), &(data.endian));
	win_ptr = mlx_new_window(mlx_ptr, data.res.x, data.res.y, "Dat_window");
	data.current_cam = data.cameras->content;
	int i = 0;
	int j = 0;

	t_vector3 l[20];
	t_vector3 n[12];
	t_vector3 p[12];

	make_dodecahedron(create_vector(0,0,0), 1, l, create_vector(0, 0.25, 0));
	compute_dode_planes(l, n, 1, create_vector(0, 0, 0));
	compute_peaks(n, p, 1, create_vector(0,0,0));
	generate_triangles(l, p, &data, encode_rgb(240, 0, 0));

	while (i < data.res.y)
	{
		if (i)
			data_adr += data.pixsizeline / 4;
		j = 0;
		while (j < data.res.x)
		{
			data.t = -1;
			data.ray = compute_ray(&data, data.cameras->content, j, i);
			t_geo *rt_obj;
			if ((rt_obj = find_closest_intersection(&data, data.ray, &data.t)))
			{
				data_adr[j] = calc_colour_from_light(data, rt_obj);
			}
			else
			{
				data_adr[j] = encode_rgb(50, 50, 50);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken is %f\n", cpu_time_used);
	mlx_loop(mlx_ptr);
	return (0);
}