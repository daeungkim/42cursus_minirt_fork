/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakim <dakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:39:03 by cjaimes           #+#    #+#             */
/*   Updated: 2020/07/06 14:20:43 by dakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "stdlib.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>
# include "mlx.h"

# define SCREEN_L 10
# define CORES 4

typedef enum		e_obj_type
{
	e_sphere = 0, e_plane = 1, e_sq = 2, e_tri = 3,
	e_cyl = 4, e_disk = 5, e_cone = 6, e_torus = 7
}					t_obj_type;

typedef struct		s_resolution
{
	int				x;
	int				y;
	int				loaded;
}					t_resolution;

typedef struct		s_rbg
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vector3;

typedef struct		s_ambiant_light
{
	double			ratio;
	int				colour;
	int				loaded;
}					t_ambiant_light;

typedef struct		s_light
{
	t_vector3		pos;
	double			ratio;
	int				colour;
}					t_light;

typedef struct		s_para_light
{
	t_vector3		direct;
	double			ratio;
	int				colour;
}					t_para_light;

typedef struct		s_camera
{
	t_vector3		pos;
	//	카메라의 위치값
	t_vector3		vector_x;
	// 보는 방향기준으로 x축에서 90도에 해당하는 값으로 추정
	t_vector3		vector_y;
	// 보는 방향기준으로 y축에서 90도에 해당하는 값으로 추정
	t_vector3		vector_z;
	// 보는 방향기준으로 z축에서 90도에 해당하는 값으로 추정
	t_vector3		orient;
	// 카메라의 보는 방향
	double			fov;
	// 카메라의 가로 화각
}					t_camera;

typedef struct		s_phere
{
	t_vector3		centre;
	double			diametre;
}					t_sphere;

typedef struct		s_plane
{
	t_vector3		centre;
	t_vector3		orient;
	t_vector3		normal;
}					t_plane;

typedef struct		s_quare
{
	t_vector3		centre;
	t_vector3		orient;
	t_vector3		normal;
	t_vector3		x;
	t_vector3		z;
	double			height;
}					t_square;

typedef struct		s_disk
{
	t_vector3		centre;
	t_vector3		orient;
	t_vector3		normal;
	double			diametre;
}					t_disk;

typedef struct		s_cylindre
{
	t_vector3		centre;
	t_vector3		real_ori;
	t_vector3		orient;
	double			diametre;
	double			height;
}					t_cylindre;

typedef struct		s_cone
{
	t_vector3		centre;
	t_vector3		normal;
	t_vector3		orient;
	double			diametre;
	double			height;
}					t_cone;

typedef struct		s_torus
{
	t_vector3		centre;
	t_vector3		normal;
	t_vector3		orient;
	double			i_dia;
	double			o_dia;
}					t_orus;

typedef struct		s_triangle
{
	t_vector3		p1;
	t_vector3		p2;
	t_vector3		p3;
	t_vector3		normal;
}					t_triangle;

typedef struct		s_rt_param
{
	t_vector3		ray;
	t_vector3		origin;
	double			i;
	int				v;
	double			i_2;
	int				v_2;
	double			i_3;
	int				v_3;
	double			i_4;
	int				v_4;
	void			*object;
}					t_rt_param;

typedef	struct		s_quartic_param
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
}					t_quartic;

typedef struct		s_geo_obj
{
	void			*obj;
	int				(*find_inter)(t_rt_param *param);
	t_vector3		(*get_normal_vector)(t_vector3 point, void *obj);
	int				colour;
	int8_t			ref;
	int8_t			gl;
	int8_t			obj_type;
}					t_geo;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
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
	t_vector3		ray_origin;
	int				ref_lvl;
	int				max_ref;
	double			t;
	// object와의 거리 저장하는 변수
	t_camera		*current_cam;
	// 이미지를 랜더링하는 현재의 카메라 저장
	t_geo			*cur_obj;
	int				bckgd_colour;
	int				no_render_amb;
	int				save;
	int				start;
	int				end;
	int				pixsize;
	int				pixsizeline;
	int				endian;
	int				out;
	int				has_ref;
}					t_data;

typedef struct		s_bmp
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
/*
** events
*/

int					proper_exit(t_data *data);
int					key_release(int key, t_data *data);
int					handle_click(int button, int x, int y, t_data *data);

/*
** parsing
*/

int					parse_error(char *err);
int					extra_info(char *err);
int					is_white_space(char c);
void				skip_whitespace(char **line);
int					check_ref(char **line);
int					ft_atoi_live(char **line);
double				ft_atof_live(char **line);
int					get_rgb(char **line, int *colour, int value);
int					get_vector3(char **line, t_vector3 *vector);
int					check_points_unique(t_vector3 p1, t_vector3 p2,
					t_vector3 p3);
int					load_res(t_data *data, char **line);
int					load_max_reflection(t_data *data, char **line);
int					load_amb(t_data *data, char **line);
int					load_light(t_data *data, char **line);
int					load_camera(t_data *data, char **line);
int					load_sphere(t_data *data, char **line);
int					load_plane(t_data *data, char **line);
int					load_square(t_data *data, char **line);
int					load_disk(t_data *data, char **line);
int					load_triangle(t_data *data, char **line);
int					load_cylinder(t_data *data, char **line);
int					load_cone(t_data *data, char **line);
int					load_torus(t_data *data, char **line);
int					load_dodecahedron(t_data *data, char **line);
int					load_cube(t_data *data, char **line);
int					load_pyramid(t_data *data, char **line);
int					load_spherocylinder(t_data *data, char **line);

/*
** vector functions
*/

t_vector3			create_vector(const double x, const double y,
					const double z);
t_vector3			add_vect(t_vector3 a, t_vector3 b);
t_vector3			sub_vect(t_vector3 a, t_vector3 b);
t_vector3			scalar_vect(t_vector3 a, double b);
double				distance(t_vector3 a, t_vector3 b);
double				magnitude(t_vector3 a);

t_vector3			point_from_ray(t_vector3 origin, t_vector3 ray, double t);
t_vector3			direction_vector(t_vector3 a, t_vector3 b);
t_vector3			normalise_vector(t_vector3 v);
double				dot(t_vector3 a, t_vector3 b);
double				dot_same(t_vector3 a);
t_vector3			cross_prod(t_vector3 a, t_vector3 b);
double				angle_between_vectors(t_vector3 a, t_vector3 b);
t_vector3			reflect_vector(t_vector3 ray, t_vector3 normal);
t_vector3			refract_vector(t_vector3 ray, t_vector3 normal, t_data *d);

t_vector3			apply_orientation(t_vector3 base, t_vector3 orient);
t_vector3			rot_axis(t_vector3 axis, t_vector3 vec, double angle);
t_vector3			get_normal_vector(t_vector3 point, t_geo *geo, t_data *d);
int					raytrace(t_geo *geo, t_rt_param *param);
t_rt_param			set_param(t_vector3 o, t_vector3 r, double i, void *ob);

/*
** ray and light
*/

t_vector3			compute_ray(const t_data *data, t_camera *cam,
					const double x, const double y);
t_geo				*find_closest_hit(t_data *data);
t_geo				*find_closest_hit_non_ref(t_data *data);
t_geo				*check_reflection(t_data *d, t_geo *hit_obj);
t_geo				*check_refraction(t_data *d, t_geo *hit_obj);
int					raytrace(t_geo *geo, t_rt_param *param);
int					calc_colour_from_light(t_data data, t_geo *rt_obj);

/*
** maths
*/

int					solve_quadratic(t_vector3 abc, double *t0, double *t1);
int					solve_square_boundaries(t_rt_param *param,
					t_square *square);
int					solve_disk_boundaries(t_rt_param *param, t_disk *disk);
int					solve_triangle_boundaries(t_rt_param *param,
					t_triangle *tri);
double				to_rad(double deg);
double				solve_poly_2(double a, double b);
void				d_swap(double *a, double *b);
int					solve_quartic(t_quartic q, t_rt_param *p);

/*
** sphere
*/

int					raytrace_sphere(t_rt_param *param);
t_vector3			normal_vector_sphere(t_vector3 point, void *sphere);

/*
** planes
*/

int					raytrace_plane(t_rt_param *param);
t_vector3			normal_vector_plane(t_vector3 point, void *plane);

/*
** square
*/

int					raytrace_square(t_rt_param *param);
t_vector3			normal_vector_square(t_vector3 point, void *square);

/*
** disk
*/

int					raytrace_disk(t_rt_param *param);
t_vector3			normal_vector_disk(t_vector3 point, void *disk);

/*
** cylinder
*/

int					raytrace_cyl(t_rt_param *param);
t_vector3			normal_vector_cyl(t_vector3 point, void *disk);

/*
** cone
*/

int					raytrace_cone(t_rt_param *param);
t_vector3			normal_vector_cone(t_vector3 point, void *con);

/*
** torus
*/

int					raytrace_torus(t_rt_param *par);
t_vector3			normal_vector_torus(t_vector3 point, void *tor);

/*
** triangle
*/

t_vector3			define_tri_plane(t_vector3 p1, t_vector3 p2, t_vector3 p3);
int					raytrace_triangle(t_rt_param *param);
t_vector3			normal_vector_triangle(t_vector3 point, void *triangle);

/*
** factories
*/

t_camera			*camera_factory(t_vector3 pos, t_vector3 vector,
					double fov);
t_light				*light_factory(t_vector3 pos, double ratio, int colour);
t_geo				*sphere_factory(t_vector3 centre, double diametre,
					int colour);
t_geo				*plane_factory(t_vector3 centre, t_vector3 normal,
					int colour);
t_geo				*square_factory(t_vector3 centre, t_vector3 normal,
						double height, int colour);
t_geo				*disk_factory(t_vector3 centre, t_vector3 orient,
						double diametre, int colour);
t_geo				*cyl_factory(t_vector3 centre, t_vector3 orient,
						t_vector3 dia_height, int colour);
t_geo				*tri_factory(t_vector3 p1, t_vector3 p2, t_vector3 p3,
					int colour);
t_geo				*cone_factory(t_vector3 centre, t_vector3 orient,
								t_vector3 dia_height, int colour);
t_geo				*torus_factory(t_vector3 centre, t_vector3 orient,
					t_vector3 i_o, int colour);

/*
** dodecahedron
*/

void				make_dode_verts(double r, t_vector3 *vertices);
void				make_dode_verts_2(t_vector3 centre, double r,
					t_vector3 *vertices, t_vector3 orient);
void				compute_dode_planes(t_vector3 *vert, t_vector3 *norm,
					double r, t_vector3 origin);
void				compute_dode_planes_2(t_vector3 *vert, t_vector3 *norm,
					double r, t_vector3 origin);
void				compute_peaks(t_vector3 *planes, t_vector3 *peaks,
					double r, t_vector3 origin);
t_list				*generate_triangles_peak_1(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_2(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_3(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_4(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_5(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_6(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_7(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_8(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_9(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_10(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_11(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_triangles_peak_12(t_vector3 *v, t_vector3 *p,
					int colour);
t_list				*generate_tri_1_5(t_vector3 *v, t_vector3 *p, int colour);
t_list				*generate_tri_6_10(t_vector3 *v, t_vector3 *p, int colour);
t_list				*generate_tri_11_12(t_vector3 *v, t_vector3 *p, int colour);
t_list				*create_dodecahedron(double radius, t_vector3 orient,
					t_vector3 centre, int colour);

/*
** pyramid
*/

int					create_roof(t_data *data, t_square *sq, double height,
					int colour);
int					create_roof_2(t_data *data, t_square *sq, double height,
					int colour);

/*
** cube
*/

int					create_cube(t_data *data, t_square *sq, int colour,
					t_vector3 o);
int					create_cube_2(t_data *data, t_square *sq, int colour);

/*
** spherocylinder
*/

int					create_endings(t_data *data, t_cylindre *cy, int colour);

/*
** render
*/

void				compute_render(t_data *data);
void				multithread_render(t_data *data);

/*
** camera
*/

int					handle_camera_movement(t_data *data, int key);
int					handle_camera_rotation(t_data *data, int key);
int					change_camera(t_data *data, int key);
int					handle_object_movement(t_data *data, int key);
int					handle_object_rotation(t_data *data, int key);

/*
** object movements
*/

void				recalc_sq_vect(t_square *sq);
void				recalc_dk_norm(t_disk *dk);
void				recalc_pl_norm(t_plane *pl);
void				recalc_cy_norm(t_cylindre *cy);
void				recalc_cone_norm(t_cone *co);
void				recalc_torus_norm(t_orus *to);
void				change_obj_normal_x_2(void *obj, short id, double val);
void				change_obj_normal_y_2(void *obj, short id, double val);
void				change_obj_normal_z_2(void *obj, short id, double val);

/*
** rgb functions
*/

int					get_blue(int colour);
int					get_green(int colour);
int					get_red(int colour);
int					encode_rgb(int red, int green, int blue);
void				decode_rgb(int colour, int *red, int *green, int *blue);
int					apply_intensity_rgb(int colour, double intensity);
int					filter_colours_rgb(int source, t_geo *obj, int lvl);
int					add_lights(int a, int b);

int					parse_error(char *err);

int					save_image(t_data *data, int x, int y);
int					load_data(t_data *data, char *rt_file);
#endif
