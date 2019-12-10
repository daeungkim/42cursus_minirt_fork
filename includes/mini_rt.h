/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:39:03 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/10 15:56:53 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

#include "stdlib.h"
#include "libft.h"
#include <math.h>
#include <pthread.h>

# define SCREEN_L 10
# define CORES 4

enum	obj_type	{e_sphere = 0, e_plane = 1, e_sq = 2, e_tri = 3, e_cyl = 4, e_disk = 5};	

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
	t_vector3	normal;
	t_vector3	x;
	t_vector3	z;
	double		height;
}				t_square;

typedef struct	s_disk
{
	t_vector3	centre;
	t_vector3	normal;
	double		diametre;
}				t_disk;

typedef struct	s_cylindre
{
	t_vector3	centre;
	t_vector3	orient;
	double		diametre;
	double		height;
}				t_cylindre;

typedef struct	s_triangle
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_vector3	normal;
}				t_triangle;

typedef struct		s_rt_param
{
	t_vector3		ray;
	t_vector3		origin;
	double			i;
	int				v;
	double			i_2;
	int				v_2;
	void			*object;
}					t_rt_param;


typedef struct		s_geo_obj
{
	void			*obj;
	int				(*find_inter)(t_rt_param *param);
	t_vector3		(*get_normal_vector)(t_vector3 point, void *obj);
	int				colour;
	int8_t			obj_type;
	//leave room for reflection
}					t_geo;

typedef struct	s_data
{
	void			*mlx_ptr;
	void 			*mlx_win;
	void			*mlx_img;
	int				*data_add;
	int				*workable;

	int				render_mode;
	int				obj_selected;
	int				cam_num;
	int				max_cam;

	t_resolution	res;
	t_ambiant_light	amb;
	t_list			*lights;
	t_list			*cameras;
	t_list			*objects;
	t_vector3		ray;
	double			t;
	t_camera		*current_cam;
	t_geo			*cur_obj;
	
	int				bckgd_colour;
	int				no_render_amb;

	int				save;

	int				start;
	int				end;

	int				pixsize;
	int				pixsizeline;
	int				endian;
}					t_data;

typedef struct 		s_bmp
{
	char			type[2];
	int				size;
	int				reserve;
	int				offset;

	int				dib_size;
	int				width;
	int				height;
	short			plane;
	short			bpp;
	int				copmression;
	int				array_size;
	int				x_res;
	int				y_res;
	int				colour;
	int				imp_colour;
}					t_bmp;


//vector functions
t_vector3	create_vector(const double x, const double y, const double z);
t_vector3	add_vect(t_vector3 a, t_vector3 b);
t_vector3	sub_vect(t_vector3 a, t_vector3 b);
t_vector3	scalar_vect(t_vector3 a, double b);
double		distance(t_vector3 a, t_vector3 b);
double		magnitude(t_vector3 a);

t_vector3	point_from_ray(t_vector3 origin, t_vector3 ray, double t);
t_vector3	direction_vector(t_vector3 a, t_vector3 b);
t_vector3	normalise_vector(t_vector3 v);
double		dot(t_vector3 a, t_vector3 b);
double		dot_same(t_vector3 a);
t_vector3	cross_prod(t_vector3 a, t_vector3 b);
double		angle_between_vectors(t_vector3 a, t_vector3 b);


t_vector3	apply_orientation(t_vector3 base, t_vector3 orient);
t_vector3	rot_axis(t_vector3 axis, t_vector3 vec, double angle);

// maths
int			solve_quadratic(t_vector3 abc, double *t0, double *t1);
int			solve_square_boundaries(t_rt_param *param, t_square *square);
int			solve_disk_boundaries(t_rt_param *param, t_disk *disk);
int			solve_triangle_boundaries(t_rt_param *param, t_triangle *tri);
double		to_rad(double deg);
double		solve_poly_2(double a, double b);
void		d_swap(double *a, double *b);

int			load_data(t_data *data, char *rt_file);

//sphere
int			raytrace_sphere(t_rt_param *param);
t_vector3	normal_vector_sphere(t_vector3 point, void *sphere);

//planes
int			raytrace_plane(t_rt_param *param);
t_vector3	normal_vector_plane(t_vector3 point, void *plane);

//square
int			raytrace_square(t_rt_param *param);
t_vector3	normal_vector_square(t_vector3 point, void *square);

//disk
int			raytrace_disk(t_rt_param *param);
t_vector3	normal_vector_disk(t_vector3 point, void *disk);

//cylinder
int	raytrace_cyl(t_rt_param *param);
t_vector3 normal_vector_cyl(t_vector3 point, void *disk);

//triangle
t_vector3	define_tri_plane(t_vector3 p1, t_vector3 p2, t_vector3 p3);
int			raytrace_triangle(t_rt_param *param);
t_vector3	normal_vector_triangle(t_vector3 point, void *triangle);

//factories
t_camera	*camera_factory(t_vector3 pos, t_vector3 vector, double fov);
t_light		*light_factory(t_vector3 pos, double ratio, int colour);
t_geo		*sphere_factory(t_vector3 centre, double diametre, int colour);
t_geo		*plane_factory(t_vector3 centre, t_vector3 normal, int colour);
t_geo 		*square_factory(t_vector3 centre, t_vector3 normal, double height, int colour);
t_geo		*disk_factory(t_vector3 centre, t_vector3 orient, double diametre, int colour);
t_geo		*cyl_factory(t_vector3 centre, t_vector3 orient, t_vector3 dia_height, int colour);
t_geo		*tri_factory(t_vector3 p1, t_vector3 p2, t_vector3 p3, int colour);

void		make_dodecahedron(t_vector3 centre, double r, t_vector3 *vertices, t_vector3 orient);
void		compute_dode_planes(t_vector3 *vert, t_vector3 *norm, double r, t_vector3 origin);
void		compute_peaks(t_vector3 *planes, t_vector3 *peaks, double r, t_vector3 origin);
void		generate_triangles(t_vector3 *vert, t_vector3 *peaks, t_data *data, int colour);

//render
void		compute_render(t_data *data);
void		multithread_render(t_data *data);

//camera
int			handle_camera_movement(t_data *data, int key);
int			handle_camera_rotation(t_data *data, int key);
int			change_camera(t_data *data, int key);
int			handle_object_movement(t_data *data, int key);

//rgb functions
int			get_blue(int colour);
int			get_green(int colour);
int			get_red(int colour);
int			encode_rgb(int red, int green, int blue);
void		decode_rgb(int colour, int *red, int *green, int *blue);
int			apply_intensity_rgb(int colour, double intensity);
int			filter_colours_rgb(int source, int surface);
int			add_lights(int a, int b);

int			save_image(t_data *data);
#endif