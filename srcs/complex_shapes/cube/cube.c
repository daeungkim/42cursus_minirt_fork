/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:14:17 by cjaimes           #+#    #+#             */
/*   Updated: 2019/12/13 00:23:24 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>
#include <stdio.h>
int create_cube(t_data *data, t_square *sq, int colour)
{
	t_vector3   o;
	t_list      *tl;
	t_vector3   new;
	t_square 	*nsq;

	o = sq->orient;
	o.z = sq->orient.z - 0.5;
	if (!(tl = ft_lstnew(square_factory(sq->centre, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	nsq = ((t_geo *)tl->content)->obj;
	new = point_from_ray(sq->centre, nsq->normal, -sq->height);
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	//ft_lstadd_back(&(data->objects), tl);
	o = sq->orient;
	o.x = nsq->orient.x - 0.25;
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	//ft_lstadd_back(&(data->objects), tl);
	o = sq->orient;
	new = point_from_ray(sq->centre, sq->normal, sq->height);
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	//ft_lstadd_back(&(data->objects), tl);
	return (1);
}

int create_cube_2(t_data *data, t_square *sq, int colour)
{
	t_vector3   o;
	t_list      *tl;
	//t_vector3   new;
	data = 0;
	//new = add_vect(sq->centre, scalar_vect(add_vect(sq->x, sq->z), -1));
	o = sq->orient;
	o.x = sq->orient.x + 0.;
	o.y = sq->orient.y + 0.25;
	o.z = sq->orient.z + 0.;
	if (!(tl = ft_lstnew(square_factory(sq->centre, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	//ft_lstadd_back(&(data->objects), tl);
	o = sq->orient;
	//o.x = sq->orient.x + 0.5;
	//o.z = sq->orient.z - 0.5;
	// if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
	// 	!((t_geo *)(tl->content)))
	// 	return (parse_error("Malloc for square failed"));
	//ft_lstadd_back(&(data->objects), tl);
	return (1);
}