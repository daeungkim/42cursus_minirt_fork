/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:39:03 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/30 17:38:07 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

#include "stdlib.h"
#include "libft.h"
#include <math.h>

# define SCREEN_L 10

typedef struct	s_resolution
{
	int			x;
	int 		y;
	int			loaded;
}				t_resolution;

typedef struct s_rbg
{
	int			r;
	int			g;
	int			b;
}				t_rgb;


typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

typedef struct	s_ambiant_light
{
	double		ratio;
	int			colour;
	int			loaded;
}				t_ambiant_light;

typedef struct	s_light
{
	t_vector3	pos;
	double		ratio;
	int			colour;
}				t_light;

typedef struct	s_camera
{
	t_vector3	pos;
	t_vector3	vector_x;
	t_vector3	vector_y;
	t_vector3	vector_z;
	t_vector3	orient;
	double		fov;
}				t_camera;

typedef struct	s_phere
{
	t_vector3	centre;
	double		diametre;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3	centre;
	t_vector3	normal;
}				t_plane;

typedef struct	s_quare
{
	t_vector3	centre;
	t_vector3	orientation;
	double		height;
}				t_square;

typedef struct	s_cylindre
{
	t_vector3	centre;
	t_vector3	orientation;
	double		diameter;
	double		height;
}				t_cylindre;

typedef struct	s_triangle
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
}				t_triangle;

typedef struct	s_data
{
	void			*ptr;
	void 			*win;
	void			*img;

	t_resolution	res;
	t_ambiant_light	amb;
	t_list			*lights;
	t_list			*cameras;
	t_list			*objects;
	t_vector3		ray;
	t_camera		*current_cam;
	int				pixsize;
	int				pixsizeline;
	int				endian;
	char 			*pixtab;

}					t_data;

typedef struct		s_rt_param
{
	t_vector3		ray;
	t_vector3		origin;
	double			intersection;
	void			*object;
}					t_rt_param;


typedef struct	s_geo_obj
{
	void *obj;
	int (*find_inter)(t_rt_param *param);
	t_vector3 (*get_normal_vector)(t_vector3 point, void *obj);
	int			colour;
	//leave room for reflection
}				t_geo;

//vector functions
t_vector3	create_vector(const double x, const double y, const double z);
t_vector3	add_vect(t_vector3 a, t_vector3 b);
t_vector3	sub_vect(t_vector3 a, t_vector3 b);
t_vector3	scalar_vect(t_vector3 a, double b);
double		distance(t_vector3 a, t_vector3 b);
double		magnitude(t_vector3 a);

t_vector3	get_point_from_ray(t_vector3 origin, t_vector3 ray, double t);
t_vector3	direction_vector(t_vector3 a, t_vector3 b);
t_vector3	normalise_vector(t_vector3 v);
double		dot_prod(t_vector3 a, t_vector3 b);
t_vector3	cross_prod(t_vector3 a, t_vector3 b);
double		angle_between_vectors(t_vector3 a, t_vector3 b);


t_vector3	apply_orientation(t_vector3 base, t_vector3 orient);

int			solve_quadratic(t_vector3 abc, double *t0, double *t1);
double		to_rad(double deg);

int			load_data(t_data *data, char *rt_file);

//sphere
int			raytrace_sphere(t_rt_param *param);
t_vector3	normal_vector_sphere(t_vector3 point, void *sphere);

//planes
int			raytrace_plane(t_rt_param *param);
t_vector3	normal_vector_plane(t_vector3 point, void *plane);

//factories
t_camera	*camera_factory(t_vector3 pos, t_vector3 vector, double fov);
t_light		*light_factory(t_vector3 pos, double ratio, int colour);
t_geo		*sphere_factory(t_vector3 centre, double diametre, int colour);
t_geo		*plane_factory(t_vector3 centre, t_vector3 normal, int colour);

//rgb functions
int			get_blue(int colour);
int			get_green(int colour);
int			get_red(int colour);
int			encode_rgb(int red, int green, int blue);
void		decode_rgb(int colour, int *red, int *green, int *blue);
int			apply_intensity_rgb(int colour, double intensity);
int			filter_colours_rgb(int source, int surface);
int			add_lights(int a, int b);

#endif