/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/29 16:44:48 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include <unistd.h>
#include <stdio.h>

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
	double sc_height;
	double sc_width;
	double pix_shift;
	t_vector3 base_dir;
	t_vector3 ray;

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

/*
** ray can be expressed with R = O + Dt with O being camera coordinates
** and D its normalised orientation vector
*/
int	raytrace_sphere(t_data *data, void *sphere, t_vector3 ray, double *intersection)
{
	t_vector3	abc;
	t_sphere	*sp;
	double		t0;
	double		t1;

	sp = (t_sphere *)sphere;
	abc.x = dot_prod(ray, ray);
	abc.y = 2 * dot_prod(ray, sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre));
	abc.z = dot_prod(sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre),
				sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre)) -
				(sp->diametre * (sp->diametre / 4.0));
	if (!solve_quadratic(create_vector(abc.x, abc.y, abc.z), &t0, &t1))
		return (0);
	*intersection = t0;
	return (1);
}

t_vector3 normal_vector_sphere(t_vector3 point, void *sphere)
{
	t_vector3 normal;
	t_sphere	*sp;

	sp = (t_sphere *)sphere;
	normal = direction_vector(sp->centre, point);
	return (normal);
}

int	raytrace(t_data *data, t_geo *geo, t_vector3 ray, double *inter)
{
	if (geo->find_inter(data, geo->obj, ray, inter))
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
	double	current;
	t_list	*first;
	
	inter_obj = 0;
	first = data->objects;
	while (first)
	{
		if (raytrace(data, first->content, ray, &current))
			if ((current > 0 && *inter < 0) || (current > 0 && current < *inter))
			{
				*inter = current;
				inter_obj = first->content;
			}
		first = first->next;
	}
	return (inter_obj);
}

double get_light_angle(t_data data, t_light *light, double t, t_geo *rt_obj)
{
	t_vector3	inter_point;
	t_vector3	normal_vect;
	t_camera	*cam;

	cam = data.current_cam;
	inter_point = get_point_from_ray(cam->pos, data.ray, t);
	normal_vect = get_normal_vector(inter_point, rt_obj);
	return (angle_between_vectors(normal_vect,
								direction_vector(inter_point, light->pos)));
}

int calc_colour_from_light(t_data data, t_geo *rt_obj, double t)
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
		angle = get_light_angle(data, light, t, rt_obj);
		if (angle < M_PI_2 && angle > -M_PI_2)
		{
			current_light = apply_intensity_rgb(light->colour, sin(M_PI_2 - angle));
			final_light = add_lights(final_light, current_light);
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
	t_data data;
	double inter;

	if (ac != 2)
		return (0);
	set_data(&data);
	load_data(&data, av[1]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data.res.x, data.res.y, "Dat_window");
	data.current_cam = data.cameras->content;
	int i = 0;
	int j = 0;
	while (i < data.res.x)
	{
		j = 0;
		while (j < data.res.y)
		{
			inter = -1;
			data.ray = compute_ray(&data, data.cameras->content, i, j);
			t_geo *rt_obj;
			if ((rt_obj = find_closest_intersection(&data, data.ray, &inter)))
			{
				mlx_pixel_put(mlx_ptr, win_ptr, i, j,
							calc_colour_from_light(data, rt_obj, inter));
			}
			else
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, encode_rgb(50,50,50));
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
	return (0);
}