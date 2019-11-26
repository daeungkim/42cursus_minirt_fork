/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/26 18:12:49 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include <unistd.h>
#include <stdio.h>
int encode_rgb(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}

double to_rad(double deg)
{
	return (deg * M_PI / 180.0);
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
	printf("current ray : |%10.6g|%10.6g|%10.6g|\n", ret.x, ret.y, ret.z);
	return (ret);
}

/*
** We adopt a standard vertical FOV of 40
** We will rotate around the Y axis for horizontal FOV and around the X axis for vertical FOV
*/
t_vector3 compute_ray(const t_data *data, t_camera *cam, const double x, const double y)
{
	double angle_h;
	double angle_v;
	t_vector3 ray;
	double temp;

	angle_h = (1.0 - x / (((double)data->res.x - 1.0)/ 2.0)) * cam->fov / 2.0;
	angle_v = (1.0 - y / (((double)data->res.y - 1.0)/ 2.0)) * cam->fov / 2.0 * ((double)data->res.y /(double)data->res.x);
	temp = cam->vector_x.x;
	ray.x = temp * cos(to_rad(angle_h)) + cam->vector_x.z * sin(to_rad(angle_h));
	ray.y = cam->vector_x.y;
	ray.z = -temp * sin(to_rad(angle_h)) + cam->vector_x.z * cos(to_rad(angle_h));
	temp = ray.x;
	ray.x = ray.x * cos(to_rad(angle_v)) - ray.y * sin(to_rad(angle_v));
	ray.y = temp * sin(to_rad(angle_v)) + ray.y * cos(to_rad(angle_v));
	return (normalise_vector(ray));
}

t_vector3 compute_ray1(const t_data *data, t_camera *cam, const double x, const double y)
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
int	raytrace_sphere(t_data *data, t_sphere *sp, t_vector3 ray, double *intersection)
{
	double a;
	double b;
	double c;
	double t0;
	double t1;

	a = dot_prod(ray, ray);
	b = 2 * dot_prod(ray, sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre));
	c = dot_prod(sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre),
				sub_vect(((t_camera *)(data->cameras->content))->pos, sp->centre)) -
				(sp->diametre * (sp->diametre / 4.0));
	if (!solve_quadratic(create_vector(a, b, c), &t0, &t1))
		return (0);
	*intersection = t0;
	return (1);
}

void set_data(t_data *data)
{
	data->res.loaded = 0;
	data->amb.loaded = 0;
	data->cameras = 0;
	data->spheres = 0;

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
	double sc_width = (double)SCREEN_L * tan(to_rad(((t_camera *)(data.cameras->content))->fov / 2.0)) * 2;
	printf("width is %g\n", sc_width);
	sc_width = sc_width * ((double)data.res.y / (double)data.res.x);
	printf("height is %g\n", sc_width);
	//t_camera *cam = data.cameras->content;
	//printf("|%10.6g|%10.6g|%10.6g|\n", cam->vector_x.x, cam->vector_x.y, cam->vector_x.z);
	while (i < data.res.x)
	{
	
		j = 0;
		while (j < data.res.y)
		{
			double inter;
			t_vector3 ray = compute_ray1(&data, data.cameras->content, i, j);
			//printf("|%10.6g, %10.6g, %10.6g|\n", ray.x, ray.y, ray.z);
			//t_vector3 ray = compute_ray(&data, i, j);
			if (raytrace_sphere(&data, data.spheres->content, ray, &inter))
			{
				//t_vector3 sphere_inter = add_vect(data.cameras->pos, scalar_vect(ray, inter));
				///printf("Sphere coordinates are |%10.7g,%10.7g,%10.7g|\n", sphere_inter.x, sphere_inter.y, sphere_inter.z);
				//double dist = distance(sphere_inter, data.spheres->centre);
				//printf("distance is %g\n", dist);
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, ((t_sphere*)(data.spheres->content))->colour);
			}
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
	return (0);
}