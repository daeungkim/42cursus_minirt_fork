/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:53:22 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/13 10:53:22 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	load_res(t_data *data, char **line)
{
	if (data->res.loaded)
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

int	load_amb(t_data *data, char **line)
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

int	load_light(t_data *data, char **line)
{
	t_vector3	coor;
	double		intensity;
	int			colour;
	t_list		*light;

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
	if (!(light = ft_lstnew(light_factory(coor, intensity, colour))) ||
			!((t_light *)(light->content)))
		return (parse_error("Malloc failed for light"));
	ft_lstadd_back(&(data->lights), light);
	return (extra_info("Light loaded"));
}

int	load_camera(t_data *data, char **line)
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
	if (vector.x > 1 || vector.y > 1 || vector.z > 1 ||
		vector.x < -1 || vector.y < -1 || vector.z < -1)
		return (parse_error("Camera orienation values not between [-1.0;1.0]"));
	skip_whitespace(line);
	if ((fov = ft_atof_live(line)) <= 0)
		return (parse_error("Error in camera fov"));
	if (!(cam = ft_lstnew(camera_factory(coor, vector, fov))) ||
			!((t_camera *)(cam->content)))
		return (0);
	ft_lstadd_back(&(data->cameras), cam);
	extra_info("Camera loaded");
	return (1);
}

int	load_max_reflection(t_data *data, char **line)
{
	if (data->max_ref > 0)
		return (parse_error("Max reflection level already loaded"));
	data->max_ref = 0;
	(*line) += 2;
	skip_whitespace(line);
	if (ft_isdigit(**line) || **line == '-')
		data->max_ref = ft_atoi_live(line);
	if (data->max_ref < 0)
		return (parse_error("Max refelction level cannot be below 0"));
	extra_info("Max reflection level set");
	return (1);
}
