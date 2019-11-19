/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:39:03 by cjaimes           #+#    #+#             */
/*   Updated: 2019/11/19 19:19:13 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

typedef struct	s_resolution
{
	int			x;
	int 		y;
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
	t_vector3	vector;
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
	t_vector3	orientation;
	int			colour;
}				t_plane;

typedef struct	s_quare
{
	t_vector3	centre;
	t_vector3	orientation;
	double		height;
	int			colour;
}				t_plane;

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

#endif