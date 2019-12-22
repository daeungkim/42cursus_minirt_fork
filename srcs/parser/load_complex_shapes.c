/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_complex_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:58:11 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/22 12:07:04 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <stdio.h>

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
	if (!(cyl = ft_lstnew(cyl_factory(centre, orient, dia_height, colour))) ||
		!((t_geo *)(cyl->content)))
		return (parse_error("Malloc for cylinder failed"));
	ft_lstadd_back(&(data->objects), cyl);
	return (extra_info("Cylinder loaded"));
}

int load_cone(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	t_vector3	dia_height;
	int 		colour;
	t_list		*con;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a cone"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a cone"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Cone orientation not between [-1.0;1.0]"));
	if ((dia_height.x = ft_atof_live(line)) <= 0)
		return (parse_error("Error in cone diametre"));
	if ((dia_height.y = ft_atof_live(line)) <= 0)
		return (parse_error("Error in cone height"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for cone"));
	if (!(con = ft_lstnew(cone_factory(centre, orient, dia_height, colour))) ||
		!((t_geo *)(con->content)))
		return (parse_error("Malloc for cone failed"));
	ft_lstadd_back(&(data->objects), con);
	return (extra_info("Cone loaded"));
}

int load_torus(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	t_vector3	i_o;
	int 		colour;
	t_list		*tor;
	
	(*line)+= 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a torus"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a torus"));
	if (orient.x > 1 || orient.y > 1 ||orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Torus orientation not between [-1.0;1.0]"));
	if ((i_o.x = ft_atof_live(line)) <= 0)
		return (parse_error("Error in torus inner diametre"));
	if ((i_o.y = ft_atof_live(line)) <= 0)
		return (parse_error("Error in torus outer diametre"));
	printf("inner = %g\n", i_o.x);
	printf("inner = %g\n", i_o.y);
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for torus"));
	if (!(tor = ft_lstnew(torus_factory(centre, orient, i_o, colour))) ||
		!((t_geo *)(tor->content)))
		return (parse_error("Malloc for cone failed"));
	ft_lstadd_back(&(data->objects), tor);
	return (extra_info("Torus loaded"));
}