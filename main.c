/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:31:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/22 19:18:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mini_rt.h"
#include "libft.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
int encode_rgb(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}

double distance(t_vector3 a, t_vector3 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}

double to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

t_vector3 create_vector(const double x, const double y, const double z)
{
	t_vector3 a;
	a.x = x;
	a.y = y;
	a.z = z;
	return (a);
}

t_vector3 add_vect(t_vector3 a, t_vector3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vector3 sub_vect(t_vector3 a, t_vector3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vector3 scalar_vect(t_vector3 a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}

t_vector3 get_point_from_ray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}

/*
** Returns a vector with a direction set by points a and b
** (vector going from a to b)
*/
t_vector3 direction_vector(t_vector3 a, t_vector3 b)
{
	b.x -= a.x;
	b.y -= a.y;
	b.z -= a.z;
	return (b);
}

/*
** Returns a vector with a length of 1
*/
t_vector3 normalise_vector(t_vector3 v)
{
	double		dist;
	t_vector3	origin;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	dist = distance(v, origin);
	v.x /= dist;
	v.y /= dist;
	v.z /= dist;
	return (v);
}

/*
** This gives ||a|| * cos(theta), theta being the angle between a and b
*/
double dot_prod(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
** cross product returns a vector perpendicular to vectors a and b
*/
t_vector3 cross_prod(t_vector3 a, t_vector3 b)
{
	t_vector3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

void draw_rect(void *mlx, void *win, int x, int y, int color, int height, int width)
{
	int scanner;

	scanner = 0;
	while (height--)
	{
		scanner = width;
		while (scanner--)
			mlx_pixel_put(mlx, win, x + scanner, y + height, color);
	}
}
/*
** We adopt a standard vertical FOV of 40
** We will rotate around the Y axis for horizontal FOV and around the X axis for vertical FOV
*/
t_vector3 compute_ray(const t_data *data, const double x, const double y)
{
	double angle_h;
	double angle_v;
	t_vector3 ray;
	double temp;

	angle_h = (1.0 - x / (((double)data->res.x - 1.0)/ 2.0)) * ((t_camera *)(data->cameras->content))->fov / 2.0;
	angle_v = (1.0 - y / (((double)data->res.y - 1.0)/ 2.0)) * ((t_camera *)(data->cameras->content))->fov / 2.0 * ((double)data->res.y /(double)data->res.x);
	temp = ((t_camera *)(data->cameras->content))->vector.x;
	ray.x = temp * cos(to_rad(angle_h)) + ((t_camera *)(data->cameras->content))->vector.z * sin(to_rad(angle_h));
	ray.y = ((t_camera *)(data->cameras->content))->vector.y;
	ray.z = -temp * sin(to_rad(angle_h)) + ((t_camera *)(data->cameras->content))->vector.z * cos(to_rad(angle_h));
	temp = ray.x;
	ray.x = ray.x * cos(to_rad(angle_v)) - ray.y * sin(to_rad(angle_v));
	ray.y = temp * sin(to_rad(angle_v)) + ray.y * cos(to_rad(angle_v));
	return (normalise_vector(ray));
}

/*
** ray can be expressed with R = O + Dt with O being camera coordinates
** and D its normalised orientation vector
*/
int	raytrace_sphere(t_data *data, t_vector3 ray, double *intersection)
{
	double a;
	double b;
	double c;
	double t0;
	double t1;

	a = dot_prod(ray, ray);
	b = 2 * dot_prod(ray, sub_vect(((t_camera *)(data->cameras->content))->pos, ((t_sphere *)(data->spheres->content))->centre));
	c = dot_prod(sub_vect(((t_camera *)(data->cameras->content))->pos, ((t_sphere *)(data->spheres->content))->centre),
				sub_vect(((t_camera *)(data->cameras->content))->pos, ((t_sphere *)(data->spheres->content))->centre)) -
				(((t_sphere *)(data->spheres->content))->diametre * (((t_sphere *)(data->spheres->content))->diametre / 4));
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
	// t_camera camera;
	// camera.fov = 40.0;
	// camera.pos = create_vector(0, 5, 0);
	// camera.vector = normalise_vector(create_vector(1, 0, 0));
	// t_sphere sphere;
	// sphere.centre = create_vector(10, 5, 3);
	// sphere.colour = encode_rgb(255, 255, 0);
	// sphere.diametre = 0.75;
	t_data data;
	set_data(&data);
	// data.cameras = &camera;
	// data.spheres = &sphere;
	// data.res.x = 1000;
	// data.res.y = 500;
	load_data(&data, av[1]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, data.res.x, data.res.y, "Dat_window");
	int i = 0;
	int j = 0;
	while (i < data.res.x)
	{
	
		j = 0;
		while (j < data.res.y)
		{
			double inter;
			t_vector3 ray = compute_ray(&data, i, j);
			if (raytrace_sphere(&data, ray, &inter))
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