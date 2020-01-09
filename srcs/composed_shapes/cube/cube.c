/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:14:17 by cjaimes           #+#    #+#             */
/*   Updated: 2020/01/09 14:08:58 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <math.h>

t_square	*get_sq(t_list *tl)
{
	return (((t_geo *)tl->content)->obj);
}

int			create_cube(t_data *data, t_square *sq, int colour, t_vector3 o)
{
	t_list		*tl;
	t_vector3	new;
	t_square	*nsq;

	if (!(tl = ft_lstnew(square_factory(sq->centre, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	nsq = ((t_geo *)tl->content)->obj;
	nsq->normal = rot_axis(normalise_vector(nsq->x), sq->normal, 0.5);
	nsq->z = rot_axis(normalise_vector(nsq->x), sq->z, 0.5);
	new = point_from_ray(sq->centre, nsq->normal, -sq->height);
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	get_sq(tl)->normal = nsq->normal;
	get_sq(tl)->z = nsq->z;
	new = point_from_ray(sq->centre, sq->normal, sq->height);
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	return (1);
}

int			create_cube_2(t_data *data, t_square *sq, int colour)
{
	t_vector3	o;
	t_list		*tl;
	t_square	*nsq;
	t_vector3	new;

	o = sq->orient;
	if (!(tl = ft_lstnew(square_factory(sq->centre, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	nsq = ((t_geo *)tl->content)->obj;
	nsq->normal = rot_axis(normalise_vector(nsq->z), sq->normal, 0.5);
	nsq->x = rot_axis(normalise_vector(nsq->z), sq->x, 0.5);
	o = sq->orient;
	new = point_from_ray(sq->centre, nsq->normal, sq->height);
	if (!(tl = ft_lstnew(square_factory(new, o, sq->height, colour))) ||
		!((t_geo *)(tl->content)))
		return (parse_error("Malloc for square failed"));
	ft_lstadd_back(&(data->objects), tl);
	get_sq(tl)->normal = nsq->normal;
	get_sq(tl)->x = nsq->x;
	return (1);
}
