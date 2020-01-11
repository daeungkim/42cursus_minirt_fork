/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_basic_shapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:53:59 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 19:00:48 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	load_sphere(t_data *data, char **line)
{
	t_vector3		centre;
	double			diametre;
	t_list			*sp;
	int				colour;

	(*line) += 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a sphere"));
	skip_whitespace(line);
	if ((diametre = ft_atof_live(line)) <= 0)
		return (parse_error("Error in sphere diametre"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for sphere"));
	if (!(sp = ft_lstnew(sphere_factory(centre, diametre, colour))) ||
			!((t_geo *)(sp->content)))
		return (parse_error("Malloc for sphere failed"));
	if (check_ref(line))
		((t_geo *)(sp->content))->ref = 1;
	ft_lstadd_back(&(data->objects), sp);
	extra_info("Sphere loaded");
	return (1);
}

int	load_plane(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	t_list		*pl;
	int			colour;

	(*line) += 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a plane"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a plane"));
	if (orient.x > 1 || orient.y > 1 || orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Plane orienation values not between [-1.0;1.0]"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for plane"));
	if (!(pl = ft_lstnew(plane_factory(centre, orient, colour))) ||
		!((t_geo *)(pl->content)))
		return (parse_error("Malloc for plane failed"));
	ft_lstadd_back(&(data->objects), pl);
	extra_info("Plane loaded");
	return (1);
}

int	load_square(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	o;
	double		height;
	int			colour;
	t_list		*sq;

	(*line) += 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a square"));
	if (!get_vector3(line, &o))
		return (parse_error("Wrong orientation vector of a square"));
	if (o.x > 1 || o.y > 1 || o.z > 1 || o.x < -1 || o.y < -1 || o.z < -1)
		return (parse_error("Square orientation not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((height = ft_atof_live(line)) <= 0)
		return (parse_error("Error in square height"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for square"));
	if (!(sq = ft_lstnew(square_factory(centre, o, height, colour))) ||
		!((t_geo *)(sq->content)))
		return (parse_error("Malloc for square failed"));
	if (check_ref(line))
		((t_geo *)(sq->content))->ref = 1;
	ft_lstadd_back(&(data->objects), sq);
	return (extra_info("Square loaded"));
}

int	load_disk(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	double		diametre;
	t_list		*dk;
	int			colour;

	(*line) += 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a disk"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a disk"));
	if (orient.x > 1 || orient.y > 1 || orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Disk orientation not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((diametre = ft_atof_live(line)) <= 0)
		return (parse_error("Error in disk diametre"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for disk"));
	if (!(dk = ft_lstnew(disk_factory(centre, orient, diametre, colour))) ||
		!((t_geo *)(dk->content)))
		return (parse_error("Malloc for disk failed"));
	ft_lstadd_back(&(data->objects), dk);
	extra_info("Disk loaded");
	return (1);
}

int	load_triangle(t_data *data, char **line)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_list		*tri;
	int			colour;

	(*line) += 2;
	if (!get_vector3(line, &p1))
		return (parse_error("Wrong p1 of a triangle"));
	if (!get_vector3(line, &p2))
		return (parse_error("Wrong p2 of a triangle"));
	if (!get_vector3(line, &p3))
		return (parse_error("Wrong p3 of a triangle"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for triangle"));
	if (!check_points_unique(p1, p2, p3))
		return (parse_error("2 or more points are not unique in triangle"));
	if (!(tri = ft_lstnew(tri_factory(p1, p2, p3, colour))) ||
		!((t_geo *)(tri->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tri);
	extra_info("Triangle loaded");
	return (1);
}
