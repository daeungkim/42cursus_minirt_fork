/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:05:18 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/05 19:21:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

int parse_error(char *err)
{
	ft_putstr("Error\n");
	ft_putstr(err);
	ft_putstr("\n");
	return (0);
}

int extra_info(char *err)
{
	ft_putstr(err);
	ft_putstr("\n");
	return (0);
}

static int is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}

static void skip_whitespace(char **line)
{
	while (is_white_space(**line))
		(*line)++;
}

int ft_atoi_live(char **line)
{
	int value;
	int sign;

	sign = 1;
	value = 0;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9' && **line)
		value = 10 * value + *(*line)++ - '0';
	return (value * sign);
}

double ft_atof_live(char **line)
{
	double value;
	double fraction;
	int sign;

	sign = 1;
	value = 0;
	fraction = 0.1;
	skip_whitespace(line);
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	while (ft_isdigit(**line))
		value = 10 * value + *(*line)++ - '0';
	if (**line == '.')
	{
		(*line)++;
		while (ft_isdigit(**line))
		{
			value += (*(*line)++ - '0') * fraction;
			fraction *= 0.1;
		}
	}
	return (value * sign);
}

int get_rgb(char **line, int *colour, int value)
{
	skip_whitespace(line);
	*colour = 0;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255 || *(*line)++ != ',')
		return (0);
	*colour = (*colour << 8) + value;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255 || *(*line)++ != ',')
		return (0);
	*colour = (*colour << 8) + value;
	if (ft_isdigit(**line))
		value = ft_atoi_live(line);
	else
		return (0);
	if (value < 0 || value > 255)
		return (0);
	*colour = (*colour << 8) + value;
	return (1);
}

int get_vector3(char **line, t_vector3  *vector)
{
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		vector->x = ft_atof_live(line);
	else
		return(0);
	if (*(*line)++ != ',')
		return (0);
	if (ft_isdigit(**line) || **line == '-')
		vector->y = ft_atof_live(line);
	else
		return(0);
	if (*(*line)++ != ',')
		return (0);
	if (ft_isdigit(**line) || **line == '-')
		vector->z = ft_atof_live(line);
	else
		return(0);
	return (1);
}

int	load_res(t_data *data, char **line)
{
	if(data->res.loaded)
		return (parse_error("Resolution already loaded"));
	data->res.x = 0;
	data->res.y = 0;
	data->res.loaded = 1;
	(*line)++;
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		data->res.x = ft_atoi_live(line);
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		data->res.y = ft_atoi_live(line);
	if (data->res.x <= 0)
		return (parse_error("Resolution X is not defined or is set to 0"));
	if (data->res.y <= 0)
		return (parse_error("Resolution Y is not defined or is set to 0"));
	extra_info("Resolution set");
	return (1);
}

int load_amb(t_data *data, char **line)
{
	if (data->amb.loaded)
		return (parse_error("Ambient light already loaded"));
	data->amb.loaded = 1;
	data->amb.ratio = -1;
	data->amb.colour = -1;
	(*line)++;
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		data->amb.ratio = ft_atof_live(line);
	if (data->amb.ratio < 0 || data->amb.ratio > 1)
		return (parse_error("Ambient light ratio not between [0.0;1.0]"));
	skip_whitespace(line);
	if (!get_rgb(line, &(data->amb.colour), 0))
		return (parse_error("Wrong RGB values for ambient light settings"));
	data->amb.colour = apply_intensity_rgb(data->amb.colour, data->amb.ratio);
	extra_info("Ambiant light loaded");
	return (1);
}

int load_light(t_data *data, char **line)
{
	t_vector3 coor;
	double	intensity;
	int		colour;
	t_list	*light;

	(*line)++;
	skip_whitespace(line);
	if (!get_vector3(line, &coor))
		return (parse_error("Wrong coordinate vector of a light"));
	skip_whitespace(line);
	if (ft_isdigit(**line))
		intensity = ft_atof_live(line);
	else
		return (parse_error("Error in a light ratio"));
	if (intensity < 0 || intensity > 1)
		return (parse_error("Light ratio not between [0.0;1.0]"));
	skip_whitespace(line);
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for light"));
	colour = apply_intensity_rgb(colour, intensity);
	if (!(light = ft_lstnew(light_factory(coor, intensity, colour))) && !((t_light *)(light->content)))
		return (parse_error("Malloc failed for light"));
	ft_lstadd_back(&(data->lights), light);
	extra_info("Light loaded");
	return (1);
}

int load_camera(t_data *data, char **line)
{
	t_vector3	coor;
	t_vector3	vector;
	double		fov;
	t_list		*cam;

	(*line)++;
	if (!get_vector3(line, &coor))
		return (parse_error("Wrong coordinate vector of a camera"));
	if (!get_vector3(line, &vector))
		return (parse_error("Wrong orientation vector of a camera"));
	if (vector.x > 1 || vector.y > 1 ||vector.z > 1 ||
		vector.x < -1 || vector.y < -1 || vector.z < -1)
		return (parse_error("Camera orienation values not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((fov = ft_atof_live(line)) <= 0)
		return (parse_error("Error in camera fov"));
	if (!(cam = ft_lstnew(camera_factory(coor, vector, fov))) && !((t_camera *)(cam->content)))
		return (0);
	ft_lstadd_back(&(data->cameras), cam);
	extra_info("Camera loaded");
	return (1);
}

int load_sphere(t_data *data, char **line)
{
	t_vector3	centre;
	double		diametre;
	int 		colour;
	t_list		*sp;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a sphere"));
	skip_whitespace(line);
	if ((diametre = ft_atof_live(line)) <= 0)
		return (parse_error("Error in sphere diametre"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for sphere"));
	if (!(sp = ft_lstnew(sphere_factory(centre, diametre, colour))) && !((t_geo *)(sp->content)))
		return (parse_error("Malloc for sphere failed"));
	ft_lstadd_back(&(data->objects), sp);
	extra_info("Sphere loaded");
	return (1);
}

int load_plane(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	int 		colour;
	t_list		*pl;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a plane"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a plane"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Plane orienation values not between [-1.0;1.0]"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for plane"));
	if (!(pl = ft_lstnew(plane_factory(centre, orient, colour))) && !((t_geo *)(pl->content)))
		return (parse_error("Malloc for plane failed"));
	ft_lstadd_back(&(data->objects), pl);
	extra_info("Plane loaded");
	return (1);
}

int load_square(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	double		height;
	int 		colour;
	t_list		*sq;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a square"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a square"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Square orientation not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((height = ft_atof_live(line)) <= 0)
		return (parse_error("Error in square height"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for square"));
	if (!(sq = ft_lstnew(square_factory(centre, orient, height, colour))) &&
		!((t_geo *)(sq->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), sq);
	extra_info("Square loaded");
	return (1);
}

int load_disk(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	double		diametre;
	int 		colour;
	t_list		*dk;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a disk"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a disk"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Disk orientation not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((diametre = ft_atof_live(line)) <= 0)
		return (parse_error("Error in disk diametre"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for disk"));
	if (!(dk = ft_lstnew(disk_factory(centre, orient, diametre, colour))) &&
		!((t_geo *)(dk->content)))
		return (parse_error("Malloc for disk failed"));
	ft_lstadd_back(&(data->objects), dk);
	extra_info("Disk loaded");
	return (1);
}

int load_cylinder(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	t_vector3	dia_height;
	int 		colour;
	t_list		*cyl;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a cylinder"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a cylinder"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Cylinder orientation not between [-1.0;1.0]"));
	if ((dia_height.x = ft_atof_live(line)) <= 0)
		return (parse_error("Error in cylinder diametre"));
	if ((dia_height.y = ft_atof_live(line)) <= 0)
		return (parse_error("Error in cylinder height"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for cylinder"));
	if (!(cyl = ft_lstnew(cyl_factory(centre, orient, dia_height, colour))) &&
		!((t_geo *)(cyl->content)))
		return (parse_error("Malloc for cylinder failed"));
	ft_lstadd_back(&(data->objects), cyl);
	extra_info("Cylinder loaded");
	return (1);
}

int check_points_unique(t_vector3 p1, t_vector3 p2, t_vector3 p3)
{
	if ((p1.x == p2.x && p1.y == p2.y && p1.z == p2.z) ||
		(p1.x == p3.x && p1.y == p3.y && p1.z == p3.z) ||
		(p2.x == p3.x && p2.y == p3.y && p2.z == p3.z))
		return (0);
	return (1);
}

int load_triangle(t_data *data, char **line)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	int 		colour;
	t_list		*tri;
	
	(*line)+= 2;
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
	if (!(tri = ft_lstnew(tri_factory(p1, p2, p3, colour))) &&
		!((t_geo *)(tri->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tri);
	extra_info("Triangle loaded");
	return (1);
}

int load_line(t_data *data, char *line)
{
	if (ft_strlen(line) < 2)
		return (1);
	if (*line == 'R')
	{
		if (!load_res(data, &line))
			return (0);
	}
	else if (*line == 'A')
	{
		if (!load_amb(data, &line))
			return (0);
	}
	else if (*line == 's' && line[1] =='p')
	{
		if (!load_sphere(data, &line))
			return (0);
	}
	else if (*line == 'p' && line[1] == 'l')
	{
		if (!load_plane(data, &line))
			return (0);
	}
	else if (*line == 's' && line[1] == 'q')
	{
		if (!load_square(data, &line))
			return (0);
	}
	else if (*line == 'd' && line[1] == 'k')
	{
		if (!load_disk(data, &line))
			return (0);
	}
	else if (*line == 'c' && line[1] == 'y')
	{
		if (!load_cylinder(data, &line))
			return (0);
	}
	else if (*line == 't' && line[1] == 'r')
	{
		if (!load_triangle(data, &line))
			return (0);
	}
	else if (*line == 'l')
	{
		if (!load_light(data, &line))
			return (0);
	}
	else if (*line == 'c')
	{
		if (!load_camera(data, &line))
			return (0);
	}
	else if (*line == '#')
		return (1);
	else
		return (parse_error("wrong input in .rt file"));
	
	return (1);
}

int load_data(t_data *data, char *rt_file)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(rt_file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			free(line);
			return (0);
		}
		if (!load_line(data, line))
		{
			extra_info("Parsing stopped.");
			free(line);
			close(fd);
			return  (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}