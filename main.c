/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/27 18:04:48 by cjaimes          ###   ########.fr       */
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
	//printf("width is %g\n", sc_width);
	sc_height = sc_width * (data->res.y / data->res.x);
	pix_shift = sc_width / ((double)data->res.x - 1);
	ray = add_vect(base_dir, scalar_vect(cam->vector_z,
									((2 * (x + 0.5) - data->res.x) / 2 )* pix_shift));
	ray = add_vect(ray, scalar_vect(cam->vector_y,
									((2 * (y + 0.5) - data->res.y) / 2) * pix_shift));
	//printf("current ray : |%10.6g,%10.6g,%10.6g|\n", ray.x, ray.y, ray.z);
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
	ac = 0;
	void *mlx_ptr;
	void *win_ptr;
	t_data data;
	set_data(&data);
	load_data(&data, av[1]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data.res.x, data.res.y, "Dat_window");
	//t_sphere *cam = (t_sphere *)data.spheres->content;
	//printf("res is %g |%g|%g|%g| |%d|\n", cam->diametre, cam->centre.x, cam->centre.y, cam->centre.z, cam->colour);
	int i = 0;
	int j = 0;
	// double sc_width = (double)SCREEN_L * tan(to_rad(((t_camera *)(data.cameras->content))->fov / 2.0)) * 2;
	// printf("width is %g\n", sc_width);
	// sc_width = sc_width * ((double)data.res.y / (double)data.res.x);
	// printf("height is %g\n", sc_width);
	// t_camera *cam = data.cameras->content;
	// printf("|%10.6g|%10.6g|%10.6g|\n", cam->vector_x.x, cam->vector_x.y, cam->vector_x.z);
	while (i < data.res.x)
	{
	
		j = 0;
		while (j < data.res.y)
		{
			double inter;
			t_vector3 ray = compute_ray(&data, data.cameras->content, i, j);
			//printf("|%10.6g, %10.6g, %10.6g|\n", ray.x, ray.y, ray.z);
			//t_vector3 ray = compute_ray(&data, i, j);
			if (raytrace(&data, data.objects->content, ray, &inter))
			{
				t_vector3 light_ray = get_point_from_ray(((t_camera *)(data.cameras->content))->pos, ray, inter);
				if (data.lights)
				{
					t_vector3 normal_vect;
					double angle;
					double perc;
					int final_color;
					int final_light;

					normal_vect = get_normal_vector(light_ray, data.objects->content);
					light_ray = direction_vector(light_ray, ((t_light *)(data.lights->content))->pos);
					angle = angle_between_vectors(normal_vect, light_ray);
					if (angle < M_PI_2 && angle > -M_PI_2)
					{
						angle = M_PI_2 - angle;
						perc = sin(angle);
						final_light = apply_intensity_rgb(((t_light *)(data.lights->content))->colour, perc);
						final_light = add_lights(final_light, data.amb.colour);
						final_color = filter_colours_rgb(final_light, ((t_geo *)data.objects->content)->colour);
						mlx_pixel_put(mlx_ptr, win_ptr, i, j, final_color);
					}
					else
					{
						final_light = data.amb.colour;
						final_color = filter_colours_rgb(final_light, ((t_geo *)(data.objects->content))->colour);
						//printf("%d\n",final_color);
						mlx_pixel_put(mlx_ptr, win_ptr, i, j, final_color);
					}
				}
				else
				{
					int final_light = data.amb.colour;
					int final_color = filter_colours_rgb(final_light, ((t_geo *)(data.objects->content))->colour);
					//printf("%d\n",final_color);
					mlx_pixel_put(mlx_ptr, win_ptr, i, j, final_color);
				}
			}
			else
			{
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, encode_rgb(25,25,25));
			}
			
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
	return (0);
}