/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_composed_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:59:06 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/11 19:10:39 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			load_dodecahedron(t_data *data, char **line)
{
	t_vector3	centre;
	t_vector3	orient;
	double		diametre;
	int			colour;
	t_list		*tris;

	(*line) += 2;
	if (!get_vector3(line, &centre))
		return (parse_error("Wrong centre vector of a dodecahedron"));
	if (!get_vector3(line, &orient))
		return (parse_error("Wrong orientation vector of a dodecahedron"));
	if (orient.x > 1 || orient.y > 1 || orient.z > 1 ||
		orient.x < -1 || orient.y < -1 || orient.z < -1)
		return (parse_error("Dode orientation not between [-1.0;1.0]"));
	if ((diametre = ft_atof_live(line)) <= 0)
		return (parse_error("Error in dodecahedron diametre"));
	if (!get_rgb(line, &colour, 0))
		return (parse_error("Wrong RGB values for dodecahedron"));
	if (!(tris = create_dodecahedron(diametre / 2, orient, centre, colour)))
		return (parse_error("Malloc for dodecahedron failed"));
	ft_lstadd_back(&(data->objects), tris);
	extra_info("Dodecahedron loaded");
	return (1);
}

static void	add_ref(void *obj)
{
	((t_geo *)obj)->ref = 1;
	return ;
}

int			load_cube(t_data *data, char **line)
{
	t_list		*sq;
	t_list		*first;
	t_geo		*obj;
	t_square	*squ;

	if (!load_square(data, line))
		return (parse_error("Base of cube failed to load"));
	sq = data->objects;
	first = sq;
	sq = ft_lstlast(sq);
	obj = sq->content;
	squ = obj->obj;
	if (!create_cube(data, obj->obj, obj->colour, squ->orient))
		return (parse_error("Part1 of cube failed to load"));
	sq = ft_lstlast(sq);
	obj = sq->content;
	if (!create_cube_2(data, obj->obj, obj->colour))
		return (parse_error("Part 2 of cube failed to load"));
	extra_info("cube loaded");
	if (check_ref(line))
		ft_lstiter(first, &add_ref);
	return (1);
}

int			load_pyramid(t_data *data, char **line)
{
	double		height;
	t_list		*sq;
	t_geo		*obj;

	if (!load_square(data, line))
		return (parse_error("Base of pyramid failed to load"));
	sq = data->objects;
	sq = ft_lstlast(sq);
	obj = sq->content;
	extra_info("base loaded");
	skip_whitespace(line);
	if ((height = ft_atof_live(line)) <= 0)
		return (parse_error("Error in pyramid height"));
	if (!create_roof(data, obj->obj, height, obj->colour))
		return (parse_error("Roof of pyramid failed to load"));
	if (!create_roof_2(data, obj->obj, height, obj->colour))
		return (parse_error("Roof of pyramid failed to load"));
	extra_info("Pyramid loaded");
	return (1);
}
