/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:00:03 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/14 11:40:29 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

int	create_roof(t_data *data, t_square *sq, double height, int colour)
{
	t_vector3	peak;
	t_vector3	p2;
	t_list		*tr;

	peak = add_vect(sq->centre, scalar_vect(add_vect(sq->x, sq->z), -0.5));
	peak = point_from_ray(peak, sq->normal, height);
	p2 = add_vect(sq->centre, scalar_vect(sq->x, -1));
	if (!(tr = ft_lstnew(tri_factory(sq->centre, p2, peak, colour))) ||
		!((t_geo *)(tr->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tr);
	p2 = add_vect(sq->centre, scalar_vect(sq->z, -1));
	if (!(tr = ft_lstnew(tri_factory(sq->centre, p2, peak, colour))) ||
		!((t_geo *)(tr->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tr);
	return (1);
}

int	create_roof_2(t_data *data, t_square *sq, double height, int colour)
{
	t_vector3	peak;
	t_vector3	p1;
	t_vector3	p2;
	t_list		*tr;

	peak = add_vect(sq->centre, scalar_vect(add_vect(sq->x, sq->z), -0.5));
	peak = point_from_ray(peak, sq->normal, height);
	p2 = add_vect(sq->centre, scalar_vect(sq->z, -1));
	p1 = add_vect(sq->centre, scalar_vect(add_vect(sq->x, sq->z), -1));
	if (!(tr = ft_lstnew(tri_factory(p1, p2, peak, colour))) ||
		!((t_geo *)(tr->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tr);
	p2 = add_vect(sq->centre, scalar_vect(sq->x, -1));
	if (!(tr = ft_lstnew(tri_factory(p1, p2, peak, colour))) ||
		!((t_geo *)(tr->content)))
		return (parse_error("Malloc for triangle failed"));
	ft_lstadd_back(&(data->objects), tr);
	return (1);
}
