/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:39:03 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/26 15:40:10 by cjaimes          ###   ########.fr       */
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
	int			colour;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3	centre;
	t_vector3	normal;
	int			colour;
}				t_plane;

typedef struct	s_quare
{
	t_vector3	centre;
	t_vector3	orientation;
	double		height;
	int			colour;
}				t_square;

typedef struct	s_cylindre
{
	t_vector3	centre;
	t_vector3	orientation;
	double		diameter;
	double		height;
	int			colour;
}				t_cylindre;

typedef struct	s_triangle
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	int			colour;
}				t_triangle;

typedef struct	s_geo_obj
{
	void *obj;
	//void (*find_inter)(void *obj, )
}				t_geo;

typedef struct	s_data
{
	void			*ptr;
	void 			*win;
	void			*img;

	t_resolution	res;
	t_ambiant_light	amb;
	t_list			*lights;
	t_list			*cameras;
	t_list			*spheres;
	t_list			*planes;
	t_list			*squares;
	t_list			*cylinders;
	t_list			*triangles;

	int				pixsize;
	int				pixsizeline;
	int				endian;
	char 			*pixtab;

}					t_data;

t_vector3	create_vector(const double x, const double y, const double z);
t_vector3	add_vect(t_vector3 a, t_vector3 b);
t_vector3	sub_vect(t_vector3 a, t_vector3 b);
t_vector3	scalar_vect(t_vector3 a, double b);
double		distance(t_vector3 a, t_vector3 b);

t_vector3	get_point_from_ray(t_vector3 origin, t_vector3 ray, double t);
t_vector3	direction_vector(t_vector3 a, t_vector3 b);
t_vector3	normalise_vector(t_vector3 v);
double		dot_prod(t_vector3 a, t_vector3 b);
t_vector3	cross_prod(t_vector3 a, t_vector3 b);


t_vector3	apply_orientation(t_vector3 base, t_vector3 orient);

int			solve_quadratic(t_vector3 abc, double *t0, double *t1);

int			load_data(t_data *data, char *rt_file);

t_camera	*camera_factory(t_vector3 pos, t_vector3 vector, double fov);
t_light		*light_factory(t_vector3 pos, double ratio, int colour);
t_sphere	*sphere_factory(t_vector3 centre, double diametre, int colour);
t_plane		*plane_factory(t_vector3 centre, t_vector3 normal, int colour);

#endif